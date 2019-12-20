#include <argList.hxx>

#include <OSspecific.hxx>
#include <Switch.hxx>
#include <clock.hxx>
#include <SubList.hxx>
#include <SortableList.hxx>
#include <JobInfo.hxx>
#include <IOobject.hxx>
#include <IFstream.hxx>
#include <IPstream.hxx>
#include <OPstream.hxx>
#include <autVersion.hxx>

AutLib::SLList<AutLib::string> AutLib::argList::validArgs;
AutLib::HashTable<AutLib::string> AutLib::argList::validOptions;
AutLib::HashTable<AutLib::string> AutLib::argList::validParOptions;
AutLib::word AutLib::argList::appDictName_("");
bool AutLib::argList::bannerEnabled(true);

AutLib::argList::initValidTables::initValidTables()
{
	validOptions.set("case", "dir");
	validOptions.set("parallel", "");
	validParOptions.set("parallel", "");
	validOptions.set("noFunctionObjects", "");

	// Add the parameters for modifying the controlDict
	// switches from the command-line

	// Instantiate a NamedEnum for the controlDict switches names
	const NamedEnum
		<
		debug::globalControlDictSwitchSet,
		debug::DIM_GLOBAL_CONTROL_DICT_SWITCH_SET
		>
		globalControlDictSwitchSetNames;

	for (label gI = 0; gI < (globalControlDictSwitchSetNames).size(); gI++)
	{
		word switchSetName = globalControlDictSwitchSetNames.names[gI];
		validOptions.set(switchSetName, "key1=val1,key2=val2,...");
	}

	validOptions.set("dumpControlSwitches", "");

	Pstream::addValidParOptions(validParOptions);
}

AutLib::argList::initValidTables dummyInitValidTables;


// convert argv -> args_
// transform sequences with "(" ... ")" into string lists in the process
bool AutLib::argList::regroupArgv(int& argc, char**& argv)
{
	int nArgs = 0;
	int listDepth = 0;
	string tmpString;

	// note: we also re-write directly into args_
	// and use a second pass to sort out args/options
	for (int argI = 0; argI < argc; argI++)
	{
		if (strcmp(argv[argI], "(") == 0)
		{
			listDepth++;
			tmpString += "(";
		}
		else if (strcmp(argv[argI], ")") == 0)
		{
			if (listDepth)
			{
				listDepth--;
				tmpString += ")";
				if (listDepth == 0)
				{
					args_[nArgs++] = tmpString;
					tmpString.clear();
				}
			}
			else
			{
				args_[nArgs++] = argv[argI];
			}
		}
		else if (listDepth)
		{
			// quote each string element
			tmpString += "\"";
			tmpString += argv[argI];
			tmpString += "\"";
		}
		else
		{
			args_[nArgs++] = argv[argI];
		}
	}

	if (tmpString.size())
	{
		args_[nArgs++] = tmpString;
	}

	args_.setSize(nArgs);

	return nArgs < argc;
}


// get rootPath_/globalCase_ from one of the following forms
//   * [-case dir]
//   * cwd
//
// Also export FOAM_CASE and FOAM_CASENAME environment variables
// so they can be used immediately (eg, in decomposeParDict)
//
void AutLib::argList::getRootCase()
{
	fileName casePath;

	// [-case dir] specified
	HashTable<string>::iterator iter = options_.find("case");

	if (iter != options_.end())
	{
		casePath = iter();
		casePath.clean();

		if (casePath.empty() || casePath == ".")
		{
			// handle degenerate form and '-case .' like no -case specified
			casePath = cwd();
			options_.erase("case");
		}
		else if (casePath[0] != '/' && casePath.name() == "..")
		{
			// avoid relative cases ending in '..' - makes for very ugly names
			casePath = cwd() / casePath;
			casePath.clean();
		}
	}
	else
	{
		// nothing specified, use the current dir
		casePath = cwd();
	}

	rootPath_ = casePath.path();
	globalCase_ = casePath.name();
	case_ = globalCase_;

	// Set the case and case-name as an environment variable
	if (rootPath_[0] == '/')
	{
		// Absolute path - use as-is
		setEnv("FOAM_CASE", rootPath_ / globalCase_, true);
		setEnv("FOAM_CASENAME", globalCase_, true);
	}
	else
	{
		// Qualify relative path
		fileName casePath = cwd() / rootPath_ / globalCase_;
		casePath.clean();

		setEnv("FOAM_CASE", casePath, true);
		setEnv("FOAM_CASENAME", casePath.name(), true);
	}
}


AutLib::stringList::subList AutLib::argList::additionalArgs() const
{
	return stringList::subList(args_, args_.size() - 1, 1);
}

AutLib::argList::argList
(
	int& argc,
	char**& argv,
	bool checkArgs,
	bool checkOpts
)
	: args_(argc)
	, options_(argc)
{
	// Check if this run is a parallel run by searching for any parallel option
	// If found call runPar (might filter argv)
	for (int argI = 0; argI < argc; argI++)
	{
		if (argv[argI][0] == '-')
		{
			const char *optionName = &argv[argI][1];

			if (validParOptions.found(optionName))
			{
				parRunControl_.runPar(argc, argv);
				break;
			}
		}
	}

	// convert argv -> args_ and capture ( ... ) lists
	// for normal arguments and for options
	regroupArgv(argc, argv);

	// Get executable name
	args_[0] = fileName(argv[0]);
	executable_ = fileName(argv[0]).name();

	// Check arguments and options, we already have argv[0]
	int nArgs = 1;
	string argListString = args_[0];

	for (int argI = 1; argI < args_.size(); argI++)
	{
		argListString += ' ';
		argListString += args_[argI];

		if (args_[argI][0] == '-')
		{
			const char *optionName = &args_[argI][1];

			if
				(
				(
					validOptions.found(optionName)
					&& validOptions[optionName] != ""
					)
					|| (
						validParOptions.found(optionName)
						&& validParOptions[optionName] != ""
						)
					)
			{
				argI++;
				if (argI >= args_.size())
				{
					FatalError
						<< "option " << "'-" << optionName << '\''
						<< " requires an argument"
						<< exit(FatalError);
				}

				argListString += ' ';
				argListString += args_[argI];
				options_.insert(optionName, args_[argI]);
			}
			else
			{
				options_.insert(optionName, "");
			}
		}
		else
		{
			if (nArgs != argI)
			{
				args_[nArgs] = args_[argI];
			}
			nArgs++;
		}
	}

	args_.setSize(nArgs);

	// Help/documentation options:
	//   -help    print the usage
	//   -doc     display application documentation in browser
	//   -srcDoc  display source code in browser
	if
		(
			options_.found("help")
			|| options_.found("doc")
			|| options_.found("srcDoc")
			)
	{
		if (options_.found("help"))
		{
			printUsage();
		}

		// only display one or the other
		if (options_.found("srcDoc"))
		{
			displayDoc(true);
		}
		else if (options_.found("doc"))
		{
			displayDoc(false);
		}

		::exit(0);
	}

	// Print the usage message and exit if the number of arguments is incorrect
	if (!check(checkArgs, checkOpts))
	{
		FatalError.exit();
	}

	// From here, we consider the command-line arguments to be valid

	string dateString = clock::date();
	string timeString = clock::clockTime();
	fileName ctrlDict = debug::controlDict().name();
	string ctrlDictString = ctrlDict.path() / ctrlDict.name();

	// Print the banner once only for parallel runs
	if (Pstream::master() && bannerEnabled)
	{
		IOobject::writeBanner(Info, true)
			<< "Build    : " << AutLib::AUTbuild << nl
			<< "Exec     : " << argListString.c_str() << nl
			<< "Date     : " << dateString.c_str() << nl
			<< "Time     : " << timeString.c_str() << nl
			<< "Host     : " << hostName() << nl
			<< "PID      : " << pid()
			<< endl;
	}

	jobInfo.add("startDate", dateString);
	jobInfo.add("startTime", timeString);
	jobInfo.add("userName", userName());
	jobInfo.add("foamVersion", word(AUTversion));
	jobInfo.add("foamBuild", AutLib::AUTbuild);
	jobInfo.add("code", executable_);
	jobInfo.add("argList", argListString);
	jobInfo.add("currentDir", cwd());
	jobInfo.add("PPID", ppid());
	jobInfo.add("PGID", pgid());


	// Case is a single processor run unless it is running parallel
	int nProcs = 1;

	// If this actually is a parallel run
	if (parRunControl_.parRun())
	{
		// For the master
		if (Pstream::master())
		{
			// establish rootPath_/globalCase_/case_ for master
			getRootCase();

			IFstream decompDictStream
			(
				rootPath_ / globalCase_ / "system/decomposeParDict"
			);

			if (!decompDictStream.good())
			{
				FatalError
					<< "Cannot read "
					<< decompDictStream.name()
					<< exit(FatalError);
			}

			dictionary decompDict(decompDictStream);

			label dictNProcs
			(
				readLabel
				(
					decompDict.lookup("numberOfSubdomains")
				)
			);

			// Check number of processors.
			// nProcs     => number of actual procs
			// dictNProcs => number of procs specified in decompositionDict
			// nProcDirs  => number of processor directories
			//               (n/a when running distributed)
			//
			// - normal running : nProcs = dictNProcs = nProcDirs
			// - decomposition to more  processors : nProcs = dictNProcs
			// - decomposition to fewer processors : nProcs = nProcDirs
			if (dictNProcs > Pstream::nProcs())
			{
				FatalError
					<< decompDictStream.name()
					<< " specifies " << dictNProcs
					<< " processors but job was started with "
					<< Pstream::nProcs() << " processors."
					<< exit(FatalError);
			}

			// distributed data
			if (decompDict.lookupOrDefault<Switch>("distributed", false))
			{
				fileNameList roots;
				decompDict.lookup("roots") >> roots;

				if (roots.size() != Pstream::nProcs() - 1)
				{
					FatalError
						<< "number of entries in decompositionDict::roots"
						<< " is not equal to the number of slaves "
						<< Pstream::nProcs() - 1
						<< exit(FatalError);
				}

				// Distribute the master's argument list (with new root)
				bool hadCaseOpt = options_.found("case");
				for
					(
						int slave = Pstream::firstSlave();
						slave <= Pstream::lastSlave();
						slave++
						)
				{
					options_.set
					(
						"case",
						fileName(roots[slave - 1]) / globalCase_
					);

					OPstream toSlave(Pstream::scheduled, slave);
					toSlave << args_ << options_;
				}
				options_.erase("case");

				// restore [-case dir]
				if (hadCaseOpt)
				{
					options_.set("case", rootPath_ / globalCase_);
				}
			}
			else
			{
				// Possibly going to fewer processors.
				// Check if all procDirs are there.
				if (dictNProcs < Pstream::nProcs())
				{
					label nProcDirs = 0;
					while
						(
							isDir
							(
								rootPath_ / globalCase_ / "processor"
								+ name(++nProcDirs)
							)
							)
					{
					}

					if (nProcDirs != Pstream::nProcs())
					{
						FatalError
							<< "number of processor directories = "
							<< nProcDirs
							<< " is not equal to the number of processors = "
							<< Pstream::nProcs()
							<< exit(FatalError);
					}
				}

				// Distribute the master's argument list (unaltered)
				for
					(
						int slave = Pstream::firstSlave();
						slave <= Pstream::lastSlave();
						slave++
						)
				{
					OPstream toSlave(Pstream::scheduled, slave);
					toSlave << args_ << options_;
				}
			}
		}
		else
		{
			// Collect the master's argument list
			IPstream fromMaster(Pstream::scheduled, Pstream::masterNo());
			fromMaster >> args_ >> options_;

			// establish rootPath_/globalCase_/case_ for slave
			getRootCase();
		}

		nProcs = Pstream::nProcs();
		case_ = globalCase_ / (word("processor") + name(Pstream::myProcNo()));
	}
	else
	{
		// establish rootPath_/globalCase_/case_
		getRootCase();
		case_ = globalCase_;
	}

	// Managing the overrides for the global control switches:
	//
	// Here is the order of precedence for the definition/overriding of the
	// control switches, from lowest to highest:
	//  - source code definitions from the various libraries/solvers
	//  - file specified by the env. variable FOAM_GLOBAL_CONTROLDICT
	//  - case's system/controlDict file
	//  - command-line parameters
	//
	// First, we allow the users to specify the location of a centralized
	// global controlDict dictionary using the environment variable
	// FOAM_GLOBAL_CONTROLDICT.
	fileName optionalGlobControlDictFileName =
		getEnv("FOAM_GLOBAL_CONTROLDICT");

	if (optionalGlobControlDictFileName.size())
	{
		debug::updateCentralDictVars
		(
			optionalGlobControlDictFileName,
			Pstream::master() && bannerEnabled
		);
	}

	// Now that the rootPath_/globalCase_ directory is known (following the
	// call to getRootCase()), we grab any global control switches overrides
	// from the current case's controlDict.

	debug::updateCentralDictVars
	(
		rootPath_ / globalCase_ / "system/controlDict",
		Pstream::master() && bannerEnabled
	);

	// Finally, a command-line override for central controlDict's variables.
	// This is the ultimate override for the global control switches.

	// Instantiate a NamedEnum for the controlDict switches names
	const NamedEnum
		<
		debug::globalControlDictSwitchSet,
		debug::DIM_GLOBAL_CONTROL_DICT_SWITCH_SET
		>
		globalControlDictSwitchSetNames;

	for (AutLib::label gI = 0; gI < (globalControlDictSwitchSetNames).size(); gI++)
	{
		word switchSetName = globalControlDictSwitchSetNames.names[gI];

		if (optionFound(switchSetName))
		{
			debug::updateCentralDictVars
			(
				globalControlDictSwitchSetNames[switchSetName],
				option(switchSetName)
			);
		}
	}

	if (optionFound("dumpControlSwitches"))
	{
		if (Pstream::master())
		{
			// Dumping the application's control switches.
			// We dump the full information to the console using a standard
			// dictionary format, so one can copy/paste this information
			//  directly into a case's system/controlDict file to
			//  override some switches values without having to always
			// use the command-line options.
			debug::dumpControlSwitchesToConsole();
		}

		::exit(0);
	}

	wordList slaveProcs;

	// collect slave machine/pid
	if (parRunControl_.parRun())
	{
		if (Pstream::master())
		{
			slaveProcs.setSize(Pstream::nProcs() - 1);
			word slaveMachine;
			label slavePid;

			label procI = 0;
			for
				(
					int slave = Pstream::firstSlave();
					slave <= Pstream::lastSlave();
					slave++
					)
			{
				IPstream fromSlave(Pstream::scheduled, slave);
				fromSlave >> slaveMachine >> slavePid;

				slaveProcs[procI++] = slaveMachine + "." + name(slavePid);
			}
		}
		else
		{
			OPstream toMaster(Pstream::scheduled, Pstream::masterNo());
			toMaster << hostName() << pid();
		}
	}


	if (Pstream::master() && bannerEnabled)
	{
		Info << "Case     : " << (rootPath_ / globalCase_).c_str() << nl
			<< "nProcs   : " << nProcs << endl;

		if (parRunControl_.parRun())
		{
			Info << "Slaves : " << slaveProcs << nl
				<< "Pstream initialized with:" << nl
				<< "    nProcsSimpleSum   : "
				<< Pstream::nProcsSimpleSum() << nl
				<< "    commsType         : "
				<< Pstream::commsTypeNames[Pstream::defaultCommsType()]
				<< endl;
		}
	}

	jobInfo.add("root", rootPath_);
	jobInfo.add("case", globalCase_);
	jobInfo.add("nProcs", nProcs);
	if (slaveProcs.size())
	{
		jobInfo.add("slaves", slaveProcs);
	}
	jobInfo.write();

	// Switch on signal trapping. We have to wait until after Pstream::init
	// since this sets up its own ones.
	sigFpe_.set(bannerEnabled);
	sigInt_.set(bannerEnabled);
	sigQuit_.set(bannerEnabled);
	sigSegv_.set(bannerEnabled);

	if (Pstream::master() && bannerEnabled)
	{
		Info << endl;
		IOobject::writeDivider(Info);
	}

	// If the macro AppSpecificDictionary is used, one can
	// modify the application-specific dictionnary using the
	// command-line parameter -appDict
	if (appDictName_ != "")
	{
		optionReadIfPresent("appDict", appDictName_);
	}
}

AutLib::argList::~argList()
{
	jobInfo.end();
}

void AutLib::argList::noBanner()
{
	bannerEnabled = false;
}


void AutLib::argList::noParallel()
{
	validOptions.erase("parallel");
}


void AutLib::argList::printUsage() const
{
	Info << nl
		<< "Usage: " << executable_;

	for
		(
			SLList<string>::iterator iter = validArgs.begin();
			iter != validArgs.end();
			++iter
			)
	{
		Info << " <" << iter().c_str() << '>';
	}

	int i = 0;
	SortableList<AutLib::string> sortedValidOptions(validOptions.size());

	for
		(
			HashTable<string>::iterator iter = validOptions.begin();
			iter != validOptions.end();
			++iter, ++i
			)
	{
		OStringStream keyValuePair;
		keyValuePair << "[-" << iter.key();

		if (iter().size())
		{
			keyValuePair << ' ' << iter().c_str();
		}

		keyValuePair << ']';
		sortedValidOptions[i] = keyValuePair.str();
	}
	sortedValidOptions.sort();

	for (AutLib::label sI = 0; sI < (sortedValidOptions).size(); sI++)
		Info << " " << sortedValidOptions[sI].c_str();

	// place help/doc/srcDoc options of the way at the end,
	// but with an extra space to separate it a little
	Info << "  [-help] [-doc] [-srcDoc]\n" << endl;
}

void AutLib::argList::displayDoc(bool source) const
{
	const dictionary& docDict = debug::controlDict().subDict("Documentation");
	List<fileName> docDirs(docDict.lookup("doxyDocDirs"));
	List<fileName> docExts(docDict.lookup("doxySourceFileExts"));

	// for source code: change foo_8C.html to foo_8C_source.html
	if (source)
	{
		for (AutLib::label extI = 0; extI < (docExts).size(); extI++)
		{
			docExts[extI].replace(".", "_source.");
		}
	}

	fileName docFile;
	bool found = false;

	for (AutLib::label dirI = 0; dirI < (docDirs).size(); dirI++)
	{
		for (AutLib::label extI = 0; extI < (docExts).size(); extI++)
		{
			docFile = docDirs[dirI] / executable_ + docExts[extI];
			docFile.expand();

			if (isFile(docFile))
			{
				found = true;
				break;
			}
		}
		if (found)
		{
			break;
		}
	}

	if (found)
	{
		string docBrowser(docDict.lookup("docBrowser"));
		docBrowser.replaceAll("%f", docFile);

		Info << "Show documentation: " << docBrowser.c_str() << endl;

		system(docBrowser);
	}
	else
	{
		Info << nl
			<< "No documentation found for " << executable_
			<< ", but you can use -help to display the usage\n" << endl;
	}
}

bool AutLib::argList::check(bool checkArgs, bool checkOpts) const
{
	bool ok = true;

	if (Pstream::master())
	{
		if (checkArgs && args_.size() - 1 != validArgs.size())
		{
			FatalError
				<< "Wrong number of arguments, expected " << validArgs.size()
				<< " found " << args_.size() - 1 << endl;
			ok = false;
		}

		if (checkOpts)
		{
			for (HashTable<string>::const_iterator iter = (options_).begin(); iter != (options_).end(); ++iter)
			{
				if
					(
						!validOptions.found(iter.key())
						&& !validParOptions.found(iter.key())
						)
				{
					FatalError
						<< "Invalid option: -" << iter.key() << endl;
					ok = false;
				}
			}
		}

		if (!ok)
		{
			printUsage();
		}
	}

	return ok;
}


bool AutLib::argList::checkRootCase() const
{
	if (!isDir(rootPath()))
	{
		FatalError
			<< executable_
			<< ": cannot open root directory " << rootPath()
			<< endl;

		return false;
	}

	if (!isDir(path()) && Pstream::master())
	{
		// Allow slaves on non-existing processor directories, created later
		FatalError
			<< executable_
			<< ": cannot open case directory " << path()
			<< endl;

		return false;
	}

	return true;
}