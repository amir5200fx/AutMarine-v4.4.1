#include <IO_IGES.hxx>

#include <Pnt3d.hxx>
#include <BRepBndLib.hxx>
#include <ShapeFix_Shape.hxx>
#include <IGESControl_Reader.hxx>

void AutLib::IO_IGES::doFixShape()
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
		cout << " ShapeExtendOK = " << fixShape->Status(ShapeExtend_OK) << std::endl;
		cout << " ShapeExtend_DONE1 = " << fixShape->Status(ShapeExtend_DONE1) << std::endl;
		cout << " ShapeExtend_DONE2 = " << fixShape->Status(ShapeExtend_DONE2) << std::endl;
		cout << " ShapeExtend_DONE3 = " << fixShape->Status(ShapeExtend_DONE3) << std::endl;
		cout << " ShapeExtend_DONE4 = " << fixShape->Status(ShapeExtend_DONE4) << std::endl;
		cout << " ShapeExtend_DONE5 = " << fixShape->Status(ShapeExtend_DONE5) << std::endl;
		cout << " ShapeExtend_DONE6 = " << fixShape->Status(ShapeExtend_DONE6) << std::endl;
		cout << " ShapeExtend_DONE7 = " << fixShape->Status(ShapeExtend_DONE7) << std::endl;
		cout << " ShapeExtend_DONE8 = " << fixShape->Status(ShapeExtend_DONE8) << std::endl;
	}

	SetShape(fixShape->Shape());
}

void AutLib::IO_IGES::ReadFile
(
	const word & theFileName,
	std::ostream& os
)
{
	IGESControl_Reader Reader;
	Reader.ReadFile(theFileName.c_str());

	Handle(TColStd_HSequenceOfTransient) myList = Reader.GiveList("iges-faces");

	SetNbIgesFaces(myList->Length());
	SetNbTransFaces(Reader.TransferList(myList));

	SetShape(Reader.OneShape());
	SetFileName(theFileName);
	SetName(theFileName);

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
		os << " IGES File Imported Successfully" << std::endl;
		os << "  - File Name: " << FileName() << std::endl;
		os << "  - Model Name: " << Name() << std::endl;
	}
}