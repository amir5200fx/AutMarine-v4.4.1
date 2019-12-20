#include <IO_STEP.hxx>

#include <Pnt3d.hxx>
#include <BRepBndLib.hxx>
#include <ShapeFix_Shape.hxx>
#include <STEPControl_Reader.hxx>

void AutLib::IO_STEP::doFixShape()
{
	Handle(ShapeFix_Shape) fixShape = new ShapeFix_Shape;

	fixShape->Init(Shape());

	Standard_Real dia = 
		Distance(BoundingBox().CornerMin(), BoundingBox().CornerMax());

	fixShape->SetPrecision(dia*Precision());
	fixShape->SetMaxTolerance(dia*MaxTol());
	fixShape->SetMinTolerance(dia*MinTol());
	fixShape->Perform();

	if (Verbosity() > 1)
	{
		cout << " ShapeExtendOK = " << fixShape->Status(ShapeExtend_OK) << endl;
		cout << " ShapeExtend_DONE1 = " << fixShape->Status(ShapeExtend_DONE1) << endl;
		cout << " ShapeExtend_DONE2 = " << fixShape->Status(ShapeExtend_DONE2) << endl;
		cout << " ShapeExtend_DONE3 = " << fixShape->Status(ShapeExtend_DONE3) << endl;
		cout << " ShapeExtend_DONE4 = " << fixShape->Status(ShapeExtend_DONE4) << endl;
		cout << " ShapeExtend_DONE5 = " << fixShape->Status(ShapeExtend_DONE5) << endl;
		cout << " ShapeExtend_DONE6 = " << fixShape->Status(ShapeExtend_DONE6) << endl;
		cout << " ShapeExtend_DONE7 = " << fixShape->Status(ShapeExtend_DONE7) << endl;
		cout << " ShapeExtend_DONE8 = " << fixShape->Status(ShapeExtend_DONE8) << endl;
	}

	SetShape(fixShape->Shape());
}

void AutLib::IO_STEP::ReadFile
(
	const word & theFileName
)
{
	STEPControl_Reader Reader;
	Reader.ReadFile(theFileName.c_str());
	
	Handle(TColStd_HSequenceOfTransient) myList = Reader.GiveList("step-faces");

	SetNbIgesFaces(myList->Length());
	SetNbTransFaces(Reader.TransferList(myList));

	SetShape(Reader.OneShape());

	Bnd_Box box;

	if (FixShape())
	{
		BRepBndLib::Add(Shape(), box);

		SetBoundingBox(box);

		doFixShape();
	}

	BRepBndLib::Add(Shape(), box);

	SetBoundingBox(box);

	if (Discrete())
	{
		BRepMesh_FastDiscret Mesh(box, theParameters_);

		Mesh.Perform(Shape());
	}

	if (Verbosity())
	{
		cout << " STEP File Imported Successfully" << endl;
	}
}