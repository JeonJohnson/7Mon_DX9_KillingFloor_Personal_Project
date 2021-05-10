#include "..\Header\SaveInfo_NaviMesh.h"



SaveInfo_NaviMesh::SaveInfo_NaviMesh()
{
}


SaveInfo_NaviMesh::~SaveInfo_NaviMesh()
{
	Safe_Delete_Arr(arrPointPosition);
	Safe_Delete_Arr(arrCellPointIndex);
}

void SaveInfo_NaviMesh::Setting(int _iPointCount, int _iCellCount)
{
	iPointCount = _iPointCount;
	arrPointPosition = new Vector3[iPointCount];

	iCellCount = _iCellCount;
	arrCellPointIndex = new Vector3[iCellCount];
}
