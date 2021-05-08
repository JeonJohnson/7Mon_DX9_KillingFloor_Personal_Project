#pragma once
#include "afxwin.h"



// NaviMeshTool_Dialog 대화 상자입니다.

class NaviPoint;
class NaviCell;
class NaviMesh;

class NaviMeshTool_Dialog : public CDialogEx
{
	DECLARE_DYNAMIC(NaviMeshTool_Dialog)

public:
	NaviMeshTool_Dialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~NaviMeshTool_Dialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NaviMesh_Dialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDeletevertexButton();

	void Update_Info();

	//void Create_NaviPoint(const Vector3& _WorldPos, GameObject* _PickingPoint = nullptr);
	

	//NaviMaker에서 안하고 여기서 다 하기.
	Vector2		m_vMousePos;
	void		Create_Ray();
	Vector3		m_vRayOrigin;
	Vector3		m_vRayDir;
	NaviPoint* Create_Sphere(const Vector3& _WorldPos, int _Index);

	void		Create_NaviPoint_First();
	
	bool		Picking_Ray2Sphere(NaviPoint** _pOutNaviPoint);
	NaviPoint*	m_pPickingPoint[2] = { nullptr };
	void		Create_NaviPoint();


	//void Pick_Sphere(int _index)
	int		m_iNaviPointIndex = 0;

	afx_msg void OnBnClickedCheckPointcreate();

	CButton m_checkPointCreate;
	bool	m_bPointCreate;
	CListBox m_PointList;

	NaviPoint*		m_pTempPoint= nullptr;
	NaviCell*		m_pTempCell = nullptr;
	NaviMesh*		m_pNaviMesh = nullptr;
};
