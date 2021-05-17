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
	afx_msg void OnBnClickedCheckPointcreate();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedNavimeshsaveButton();
	afx_msg void OnBnClickedNavimeshloadButton();
	afx_msg void OnLbnSelchangeListNavipointlist();

	void Update_Info();

	//void Create_NaviPoint(const Vector3& _WorldPos, GameObject* _PickingPoint = nullptr);
	

	//NaviMaker에서 안하고 여기서 다 하기.
	class Camera* m_pMainCam = nullptr;
	Vector2		m_vMousePos;
	void		Create_Ray();
	Vector3		m_vRayOrigin;
	Vector3		m_vRayDir;
	NaviPoint* Create_Sphere(const Vector3& _WorldPos, int _Index);

	void		Create_NaviPoint_First();
	
	bool		Picking_Ray2Sphere(NaviPoint** _pOutNaviPoint);
	NaviPoint*	m_pPickingPoint[3] = { nullptr };
	void		Create_NaviPoint();

	//void Pick_Sphere(int _index)
	int		m_iNaviPointIndex = 0;
	int		m_iCellIndex = 0;



	CButton m_checkPointCreate;
	bool	m_bPointCreate;
	


	NaviPoint*		m_pTempPoint= nullptr;
	map<int, NaviPoint*>	m_mapPoint;
	NaviPoint*		m_pSelectPoint = nullptr;
	NaviCell*		m_pTempCell = nullptr;
	//list<NaviCell>
	NaviMesh*		m_pNaviMesh = nullptr;

	CListBox	m_PointList;
	int			m_iCurIndex = -1;
	
	Vector3		m_vPointPostion;
	CString		m_csPointPosX;
	float		m_fPointPosX;
	CString		m_csPointPosY;
	float		m_fPointPosY;
	CString		m_csPointPosZ;
	float		m_fPointPosZ;

	
	afx_msg void OnEnChangeVerposxEdit();
	afx_msg void OnEnChangeVerposyEdit();
	afx_msg void OnEnChangeVerposzEdit();
};
