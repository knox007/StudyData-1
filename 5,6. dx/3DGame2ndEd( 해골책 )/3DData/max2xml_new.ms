-- Filename		: max2xml.ms
-- Made by		: 김용준(http://3dstudy.net, newtype@chol.com), 한국콘텐츠진흥원 소속
-- License		: LGPL
-- System  		: Tested on MAX 2010.x
-- Target API	: Direct 3D
-- Version      : 0.9 beta
-- 1st Revision : 2003.02.24
-- 2nd Revision : 2003.03.04(composite material fixed)
-- 3rd Revision : 2003.03.16(Bounding Box export)
-- 4th Revision : 2003.03.28('count' attribute removed, 'parent' element changed to attribute, doubtful hasproperty func -_- )
-- 5th Revision : 2003.04.03(<Opacity> added at Material Element)
-- 6th Revision : 2003.04.19(BoneTable을 일반 오브젝트외에 따로 추가하여 관리), physique, skin modifier자동 선택
-- 7th Revision : 2003.07.21(실제로 전용 파서를 만들면서 버그패치)
-- 8th Revision : 2004.10.05(Helper지원 추가 DumpObjects함수 수정)
-- 9th Revision : 2005.05.23(material지원 수정, camera지원 추가)
--10th Revision : 2005.07.07(material editor의 확장 plugin추가, 미리보기 추가, 스타트업스크립트로 변경)
-- To Do        : Vertex Normal에 이상있음

-- XML Element string
g_strBody			= "Body"
g_strInfo			= "Info"
g_strFilename		= "Filename"
g_strObjectCount	= "ObjectCount"
g_strMeshCount		= "MeshCount"
g_strAniStart		= "AnimationStart"
g_strAniEnd			= "AnimationEnd"
g_strTypeKey		= "KeyType"			-- KeyFrame, Sampling(ik,biped)
g_strFrameRate		= "FrameRate"

g_strMaterial		= "Material"
g_strSlot			= "Slot"
g_strObject			= "Object"
g_strFace			= "Face"
g_strTriVertex		= "Vertex"
g_strVertexNormal	= "VertexNormal"
g_strTriIndex		= "TriIndex"
g_strTexVertex		= "TexVertex"
g_strTexIndex		= "TexIndex"
g_strVertexWeight	= "VertexWeight"
g_strLocalTM		= "LocalTM"
g_strWorldTM		= "WorldTM"
g_strParent			= "Parent"
g_strKey			= "Key"
g_strValue			= "Value"
g_strPosition		= "Position"
g_strRotation		= "Quaternion"
g_strScale			= "Scale"
g_strBoundingBox	= "BoundingBox"
g_strMax			= "Max"
g_strMin			= "Min"
g_strCenter			= "Center"
g_strBone			= "Bone"

g_strMtrlDiffuse	= "Diffuse"
g_strMtrlAmbient	= "Ambient"
g_strMtrlSpecular	= "Specular"
g_strMtrlEmissive	= "Emissive"
g_strMtrlOpacity	= "Opacity"
g_strMtrlPower		= "Power"
g_strMtrlMapDiffuse	= "DiffuseMap"
g_strMtrlMapSpecualr= "SpecularMap"
g_strMtrlMapBump	= "BumpMap"
g_strMtrlMapDisplace= "DisplacementMap"

-- XML Attribute string
g_strID				= "ID"
g_strBoneID			= "BoneID"
g_strIndex			= "Index"
g_strName			= "Name"
g_strClass			= "Class"
g_strBoneCount		= "BoneCount"
g_strMtrlCount		= "MaterialCount"
g_strMtrlID			= "MaterialID"
g_strFrameNo		= "Frame"

g_uiObjectName		= 0
g_uiProgress		= 0

g_nObjectIDRef		= 1
g_bObjectIDWithName = true
g_bMultiplyQuaternion = false
g_bSampling			= false
g_nSampling			= 1
g_strKeyType		= "Keyframe"
g_snapObjects		= undefined

-- [MAX quaterion]            [D3D quaternion]
-- x,y,z,w                    -x,-z,-y,w

-- [D3D matrix]               [MAX matrix]
-- _11 _12 _13 0              _11 _13 _12 0
-- _21 _22 _23 0       <->    _31 _33 _32 0
-- _31 _32 _33 0              _21 _23 _22 0
-- _41 _42 _43 1              _41 _43 _42 1

-- Basic type definitions
struct MATRIX_D3D
( 
	_11, _12, _13, _14,
	_21, _22, _23, _24,
	_31, _32, _33, _34,
	_41, _42, _43, _44
)

struct MTRL_ID_FACE
(
	ID,
	faceSet
)

struct BONE_WEIGHT
(
	strName,		-- bone name
	weight
)

struct OBJECT_WEIGHT
(
	nBoneCount,
	vertexSet
)

fn FindObject name =
(
	for o in objects do
	(
		if o.name == name then return o
	)
	
	undefined
)

-- qsort는 struct를 지원하지 않는다.(적어도 테스트 해본 결과는 그렇다.)
-- 아래의 문장을 돌려보면 struct배열에서 qsort가 작동하지 않는것을 확인할 수 있다.
--struct T 
--( 
--	name, 
--	weight 
--)
--arr = #()
--for i=1 to 3 do
--(
--	local tmp = T 0 0
--	tmp = T (i as string) (random 0.0 1.0)
--	append arr tmp
--)
--
--"before"
--for i in arr do print i 
--"after"
--qsort arr (fn compare v1 v2 = (v2.weight- v1.weight))
--for i=1 to a.count do print arr[i]

-- 간단한 거품정렬함수
fn mysort arr fnCompare = 
(
	for i = 1 to arr.count do
		for j = i to arr.count do
		(
			if (fnCompare arr[i] arr[j]) > 0 then
			(
				t = arr[i]
				arr[i] = arr[j]
				arr[j] = t
			)
		)
)

struct ZUtility
(
	m_varSetObjectNames = #(),		-- object의 이름대신 ID값을 사용하기위한 table
	m_varSetBoneNames = #(),
	m_varSetMaterials = #(),		-- 현재 scene에서 사용중인 모든 material table
	
	-- 정의 : collect을 할때 겹치지 않게 collect한다.
	-- 설명 : 단순히 append하면 동일한 object가 중복 collect될수 있다.
	fn SafeAppend sets item =
	(
		for i = 1 to sets.count do
		(
			if sets[i] == item then
			(
				return undefined
			)
		)
		
		append sets item
	),
	
	-- 정의 : object의 이름대신 ID값을 사용하기위한 table을 만든다.
	-- 주의 : Constructor()에서 자동으로 불린다.
	fn CollectNames =
	(
		temp = dummy()
		temp.name = "NULL"
		SafeAppend m_varSetObjectNames temp.name
		for o in objects do
		(
			-- 프로즌 되어 있는 노드는 포함하지 않는다.
			if o.isFrozen == false then
			(
				SafeAppend m_varSetObjectNames o.name
			)
		)
	),
	
	-- 정의 : material의 이름대신 ID값을 사용하기위한 table을 만든다.
	-- 주의 : Constructor()에서 자동으로 불린다.
	fn CollectMaterials =
	(
		temp = standard()
		SafeAppend m_varSetMaterials temp	--material을 지정하지 않은 오브젝트는 0번 재질을 사용한다.
		for i = 1 to objects.count do
		(
			if objects[i].material == undefined do continue
			if classof objects[i].material == Standardmaterial then			-- material이 하나일 경우
			(
				SafeAppend m_varSetMaterials objects[i].material
			)
			
			if classof objects[i].material == Multimaterial then				-- materials이 여러개일 경우
			(
				for j = 1 to objects[i].material.count do
				(
					SafeAppend m_varSetMaterials objects[i].material[j]
				)
			)
		)
	),
	
	fn CollectBoneID = 
	(
		SafeAppend m_varSetBoneNames "NULL"
		for o in objects do
		(
			if ( classOf o == Biped_Object ) or ( classOf o == BoneGeometry ) or ( classOf o == bone ) or ( superclassof o == helper ) then
			(
				-- 프로즌 되어 있는 노드는 포함하지 않는다.
				if o.isFrozen == false then
				(
					SafeAppend m_varSetBoneNames o.name
				)
			)
		)
	),
	
	fn GetBoneID obj =
	(
		if obj != undefined then
		(
			for i = 1 to m_varSetBoneID.count do
			(
				if obj.name == m_varSetBoneNames[i] do return i-1
			)
		)
		0
	),
	
	fn GetBoneIDByName obj_name =
	(
		if obj_name != undefined then
		(
			for i = 1 to m_varSetBoneNames.count do
			(
				if obj_name == m_varSetBoneNames[i] do return i-1
			)
		)
		0
	),
	
	-- 정의 : object의 ID값을 돌려준다.
	--        실패할 경우 0을 돌려준다.
	fn GetObjectID obj =
	(
		if obj != undefined then
		(
			for i = 1 to m_varSetObjectNames.count do
			(
				if obj.name == m_varSetObjectNames[i] do return i
			)
		)
		0
	),		
	
	-- 정의 : object의 ID값을 돌려준다.
	--        실패할 경우 0을 돌려준다.
	fn GetObjectIDByName obj_name =
	(
		if obj_name != undefined then
		(
			for i = 1 to m_varSetObjectNames.count do
			(
				if obj_name == m_varSetObjectNames[i] do return i
			)
		)
		0
	),		
	
	-- 정의 : material의 ID값을 돌려준다.
	--        실패할 경우 0을 돌려준다.
	fn GetMaterialID mtrl =
	(
		if mtrl != undefined then
		(
			for i = 1 to m_varSetMaterials.count do
			(
				if m_varSetMaterials[i] == mtrl do return i
			)
		)		
		0
	),
	
		
	-- 정의 : MAX의 TM을 D3D의 TM으로 바꿔준다.
	fn ConvertToD3D_TM max_tm =
	(
		local	d3d_tm = MATRIX_D3D	0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
		d3d_tm._11 = max_tm.row1.x
		d3d_tm._12 = max_tm.row1.z
		d3d_tm._13 = max_tm.row1.y
		d3d_tm._14 = 0.0
		
		d3d_tm._21 = max_tm.row3.x
		d3d_tm._22 = max_tm.row3.z
		d3d_tm._23 = max_tm.row3.y
		d3d_tm._24 = 0.0
		
		d3d_tm._31 = max_tm.row2.x
		d3d_tm._32 = max_tm.row2.z
		d3d_tm._33 = max_tm.row2.y
		d3d_tm._34 = 0.0
		
		d3d_tm._41 = max_tm.row4.x
		d3d_tm._42 = max_tm.row4.z
		d3d_tm._43 = max_tm.row4.y
		d3d_tm._44 = 1.0
		
		d3d_tm
	),
	
	-- 정의 : MAX의 POS좌표를 D3D의 POS좌표로 바꿔준다.
	fn ConvertToD3D_POS max_pos =
	(
		local	d3d_pos = [0,0,0]
		d3d_pos.x = max_pos.x
		d3d_pos.y = max_pos.z
		d3d_pos.z = max_pos.y
		
		d3d_pos
	),
	
	-- 정의 : MAX의 QUATERNIONS좌표를 D3D의 좌표로 바꿔준다.
	-- MAX_quat -> D3D_quat
	-- x,y,z,w  -> -x,-z,-y,w
	fn ConvertToD3D_QUAT max_quat =
	(
		local	d3d_quat = quat 0 0 0 0
		d3d_quat.x = -max_quat.x
		d3d_quat.y = -max_quat.z
		d3d_quat.z = -max_quat.y
		d3d_quat.w =  max_quat.w
		
		d3d_quat
	),
	
	-- 정의 : MAX의 텍스쳐 좌표를 D3D의 uv좌표로 바꿔준다.
	fn ConvertToD3D_UV max_pos =
	(
		local	d3d_uv = [0,0]
		d3d_uv.x = max_pos.x
		d3d_uv.y = 1.0 - Max_pos.y
		
		d3d_uv
	),
	
	-- 정의 : MAX의 vertex index를 D3D의 index 순서로 바꿔준다.
	fn ConvertToD3D_INDEX max_index =
	(
		local d3d_index = [0,0,0]
		d3d_index.x = max_index.x - 1
		d3d_index.y = max_index.z - 1
		d3d_index.z = max_index.y - 1
		
		d3d_index
	),
	
	-- 정의 : class로 object를 선택해주는 함수
	-- 사용 :
	-- a = GetObjectsBySuperClass Editable_mesh
	-- print "a="
	-- for i in a do print (classof i)
	fn GetObjectsByClass cl =
	(
		varSetSameClass = #()
	
		for o in objects do
		(
			if classOf o == cl then 
			(
				append varSetSameClass o
			)
		)
		
		varSetSameClass	
	),
	
	-- 정의 : class로 object를 선택해주는 함수
	-- 사용 :
	-- a = GetObjectsBySuperClass Editable_mesh
	-- print "a="
	-- for i in a do print (classof i)
	fn GetObjectsBySuperClass cl =
	(
		varSetSameClass = #()
	
		for o in objects do
		(
			if SuperClassOf o == cl then 
			(
				append varSetSameClass o
			)
		)
		
		varSetSameClass	
	),
	
	-- 정의 : Biped 오브젝트를 배열로 리턴한다.
	-- 사용 : a = GetObjects_Biped()
	fn GetObjects_Biped =
	(
		GetObjectsByClass Biped_Object
	),
	
	-- 정의 : Bone 오브젝트를 배열로 리턴한다.
	-- 사용 : b = GetObjects_BoneGeometry()
	fn GetObjects_BoneGeometry =
	(
		GetObjectsByClass BoneGeometry
	),
	
	-- 정의 : Editable Mesh를 배열로 리턴한다.
	-- 사용 : c = GetObjects_Mesh()
	fn GetObjects_Mesh =
	(
		GetObjectsByClass Editable_mesh
	),
	
	-- 정의 : Hierarchy를 고려한 Local Transform Matrix(TM)를 리턴한다.
	fn GetLocalTM obj =
	(
		local matLocal = copy obj.transform
		if obj.parent != undefined then
		(
			matLocal = obj.transform * ( inverse obj.parent.transform )
		)
		
		matLocal
	),
	
	-- 정의 : Pivot을 고려한 Local Vertex를 리턴한다.
	-- 주의 : in coordsys local getvert obj i하면 손쉽게 local vertex를 구할수 있다고
	--        생각할수 있으나, MAX에서 pivot은 local좌표계의 원점이 아니라 회전의 중심축일 뿐이다.
	--        그래서 local vertex를 직접 구하면 pivot을 무시한 잘못된 local vertex를 구하게 된다.(offset연산이 필요하다.)
	--        이 함수에서는 world vertex를 구해서 inverse tm을 곱하는 방법을 사용하고 있다.
	fn GetLocalVertices obj =
	(
		varSetVertex= #()
		
		TM = obj.transform
		InvTM = inverse TM
		
		for i = 1 to obj.mesh.numverts do
		(
			local vl -- vertex local
			local vw -- vertex world
			vw = in coordsys world getvert obj.mesh i
			vl = vw * InvTM
			append varSetVertex vl
		)
		
		varSetVertex
	),
	
	-- 정의 : vertex의 normal을 리턴한다.
	fn GetVertexNormals obj =
	(
		varSetNormal = #()
		for i = 1 to obj.mesh.numverts do
		(
			local n
			append varSetNormal (getnormal obj.mesh i)
		)
		
		varSetNormal
	),
	
	-- 정의 : Skin modifier로 구성된 vertex의 weight를 리턴한다.
	fn GetVertexWeightsBySkin obj =
	(
		ow = OBJECT_WEIGHT 0 #()
		
		if superclassof obj != GeometryClass then return undefined		-- skin은 mesh에 붙는다.
		local sm														-- skin object
		max modify mode													-- max를 modify mode로 변환
		sm = obj.modifiers[#Skin]										-- skin modifier
		if sm == undefined then return undefined						-- 이 mesh는 skin이 없군
	 	modPanel.setCurrentObject sm									-- mesh의 modifier중에서 skin을 선택한다.
		if obj.numverts == 0 then return undefined						-- vertex가 없는데 뭘 어쩌라구?
		
		nBoneCount = SkinOps.GetNumberBones sm							-- 적용된 bone이 몇개지?
		nVertCount = SkinOps.GetNumberVertices sm						-- 이 skin에서 제어하는 vertex의 갯수는?
		if nVertCount == 0 then return undefined						-- 제어하는 vertex가 없는데 뭘 어쩌라구?
		
		ow.nBoneCount = nBoneCount
		for i = 1 to nVertCount do
		(
			nVertexWeightCount = SkinOps.GetVertexWeightCount sm i		-- vertex i에 적용된 weight(가중치)의 갯수
			local bwSet = #()
			for j = 1 to nVertexWeightCount do
			(
				nBoneID = SkinOps.GetVertexWeightBoneID sm i j			-- 어느 bone에서 가중치를 적용하고 있나? bone의 ID
				local strTemp = SkinOps.GetBoneName sm nBoneID 0		-- 가중치 적용중인 bone의 이름
				local wTemp = SkinOps.GetVertexWeight sm i j			-- vertex에 적용중인 bone의 가중치 값(0.0 ~ 1.0)
				local bw = BONE_WEIGHT 0 0
				bw.strName = strTemp
				bw.weight = wTemp
				append bwSet bw
			)
			append ow.VertexSet bwSet
		)
		ow
	),
		
	-- 정의 : Physique modifier로 구성된 vertex의 weight를 리턴한다.
	--        이 함수를 사용하기 위해서는 IPhysique.gup 플러그인이 필요하다.
	function GetVertexWeightsByPhysique obj = 
	( 
		ow = OBJECT_WEIGHT 0 #()
		if superclassof obj != GeometryClass then return undefined		-- skin은 mesh에 붙는다.
		
		max modify mode													-- max를 modify mode로 변환
		pm = physiqueOps.getPhysiqueModifier obj 
		bones = physiqueOps.getBones obj modifier:pm
		nVertCount = physiqueOps.getVertexCount obj modifier:pm
		if bones != undefined then nBoneCount = bones.count
		else return undefined
		
		if nVertCount == 0 then return undefined						-- 제어하는 vertex가 없는데 뭘 어쩌라구?
		
		ow.nBoneCount = nBoneCount
		for i = 1 to nVertCount do
		( 
			nVertexWeightCount = physiqueOps.getVertexBoneCount obj i modifier:pm
			local bwSet = #()
			for j = 1 to nVertexWeightCount do 
			(
				local strTemp = (physiqueOps.getVertexBone obj i j modifier:pm).name
				local wTemp = (physiqueOps.getVertexWeight obj i j modifier:pm)
				local bw = BONE_WEIGHT 0 0
				bw.strName = strTemp
				bw.weight = wTemp
				append bwSet bw
			) 
			append ow.VertexSet bwSet
		) 
		ow
	),
	
	
	-- 정의 : materialID와 동일한 face들을 collect해서 리턴한다
	fn GetFacesByMaterial obj materialID =
	(
		faceSet = #()
		for i = 1 to obj.faces.count do
		(
			if (getfacematid obj i ) == materialID then
			(
				append faceSet i
			)
		)
		
		faceSet
	),
	
	-- 정의 : object를 동일한 face들끼리 묶어서 group화 한다.
	fn SplitFacesByMaterial obj =
	(
		fmSet = #()
		
--		if obj.material == undefined then return undefined

		if classOf obj.material == UndefinedClass then
		(
			local fm = MTRL_ID_FACE 0 #()
			fm.id = 0
			for i = 1 to obj.mesh.faces.count do ( append fm.faceSet i )
			append fmSet fm
		)
		
		if classOf obj.material == Standardmaterial then
		(
			local fm = MTRL_ID_FACE 0 #()
			fm.id = GetMaterialID obj.material
			for i = 1 to obj.mesh.faces.count do ( append fm.faceSet i )
			append fmSet fm
		)
		
		if classOf obj.material == Multimaterial then
		(
			for i = 1 to obj.material.count do
			(
				local fm = MTRL_ID_FACE 0 #()
				fm.id = GetMaterialID obj.material[i]
				fm.faceSet =  GetFacesByMaterial obj i
				if fm.faceSet.count != 0 then ( append fmSet fm )
			)
		)
		
		fmSet
	),

	-- 정의 : face 들을 material 별로 정렬하여 바뀐 인덱스를 배열로 만든다.
	fn FacesByMaterial obj =
	(
		faceSet = #()

		--if obj.material == undefined then return undefined

		if classOf obj.material == UndefinedClass then
		(
			for i = 1 to obj.faces.count do ( append faceSet i )
		)

		if classOf obj.material == Standardmaterial then
		(
			for i = 1 to obj.faces.count do ( append faceSet i )
		)

		if classOf obj.material == Multimaterial then
		(
			for i = 1 to obj.material.count do
			(
				join faceSet (GetFacesByMaterial obj i)
			)
		)

		faceSet
	),	
		
	-- 정의 : Biped나 IK사용시 키값을 추출하기 위해서 TM샘플링을 사용하고 있다.
	--        이때, snapshot으로 임시 오브젝트를 생성하여 TM값을 샘플링(Sampling or Dump)한다.
	fn DumpObjects obj =
	(
	    origbiped = #()
	    snapset = #()

		if obj == helper then ( select (GetObjectsBySuperClass obj) )
		else ( select (GetObjectsByClass obj) )
	    
	    selectionSets ["OrigBiped"] = selection
	
	    for i in selection do 
	    (
	        append origbiped i
	        b = snapshot i name:(i.name as string + "_snap")
	        b.parent = undefined
	        b.transform = i.transform
	        b.position.track = bezier_position()
	        b.rotation.track = tcb_rotation()
	        append snapset b
	    )
	    selectionSets ["Snapset"] = Snapset
	    
	    for i in 1 to snapset.count do
	    (
	        try
	        (
	            snapset[i].parent = execute ("$'" + origbiped[i].parent.name + "_snap'")
	        )
	        catch()
	    )
	    
		for i in 1 to Snapset.count do
		(
			--h = execute ("$" + selectionSets["Linkset"][i].name + "_Scrpt")
			snapset[i].position.track = bezier_position()
			snapset[i].rotation.track = tcb_rotation() --euler_xyz()
		)
		 
	    animate on
	    undo off
	    for t = animationRange.start to animationRange.end by g_nSampling do at time t
	    (
	        for i in 1 to Snapset.count do
	        (
	            snapset[i].transform = origbiped[i].transform
	        )
	    )
	    
	    snapset
	--	g_snapObjects = SnapSet
	),

	-- 정의 : 최초 스크립트를 초기화 한다.
	-- 설명 : 현재 scene의 object-id table과 material table을 만든다.
	fn Constructor =
	(
		CollectNames()	
		CollectMaterials()
		CollectBoneID()
	),
	
	fn Destructor = 
	(
		if $ != undefined then deselect $
		select $'NULL'
		delete $
	)
)

---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------

struct ZExport
(
	m_oUtil = 0,
	m_strFilename = 0,
	m_fileTarget = 0,
	m_strAttrName = #(),
	m_strAttrValue = #(),
	
	fn Constructor =
	(
		m_oUtil = ZUtility #() #()
		m_oUtil.Constructor()		-- 객체 초기와
		
		if m_strFilename == "debug" then
		(
			m_fileTarget = newScript()
		)
		else
		(
			format "Creating %...\n" m_strFilename
			m_fileTarget = createFile m_strFilename
		)
	),
	
	fn Destructor =
	(
		m_oUtil.Destructor()
		if m_strFilename != "debug" then
		( 
			close m_fileTarget
		)
	),

	fn StackClearAttr =
	(
		m_strAttrName = #()
		m_strAttrValue = #()
	),
	
	fn StackPushAttr vName vValue =
	(
		append m_strAttrName vName
		append m_strAttrValue vValue
	),
	
	fn XMLElementBegin nTabCount ElementName bCR =
	(
		local str = ""
		for i = 1 to nTabCount do ( str += "\t" )
		
		str += ("<" + ElementName)
		if m_strAttrName != undefined then
		(
			for i = 1 to m_strAttrName.count do
			(
				str += " "
				str += ( m_strAttrName[i] + "=" )
				str += ( "\"" + (m_strAttrValue[i] as string) + "\"" )
			)
		)
		if bCR == true then
		(
			str+=">\n"
		)
		else
		(
			str += ">"
		)
		
		format "%" str to:m_fileTarget
	),
	
	fn XMLElementEnd nTabCount ElementName =
	(
		local str = ""
		for i = 1 to nTabCount do
		(
			str += "\t"
		)
		str += ("</" + ElementName + ">\n")
		format "%" str to:m_fileTarget
	),
	
	fn WriteParent obj nTabCount =
	(
		StackClearAttr()
		StackPushAttr g_strID ((m_oUtil.GetObjectID obj.parent) - g_nObjectIDRef)
		if g_bObjectIDWithName then
		(
			if obj.parent != undefined then
			(
				StackPushAttr g_strName obj.parent.name
			)
			else
			(
				StackPushAttr g_strName "undefined"
			)
		)
		XMLElementBegin nTabCount g_strParent true
		XMLElementEnd nTabCount g_strParent
	),
	
	fn WriteTM obj nTabCount =
	(
		StackClearAttr()
		XMLElementBegin nTabCount g_strLocalTM true
		tm = m_oUtil.ConvertToD3D_TM (m_oUtil.GetLocalTM obj)
			XMLElementBegin (nTabCount+1) g_strValue false
			format "[%,%,%,%]" tm._11 tm._12 tm._13 tm._14 to:m_fileTarget
			XMLElementEnd 0 g_strValue
			XMLElementBegin (nTabCount+1) g_strValue false
			format "[%,%,%,%]" tm._21 tm._22 tm._23 tm._24 to:m_fileTarget
			XMLElementEnd 0 g_strValue
			XMLElementBegin (nTabCount+1) g_strValue false
			format "[%,%,%,%]" tm._31 tm._32 tm._33 tm._34 to:m_fileTarget
			XMLElementEnd 0 g_strValue
			XMLElementBegin (nTabCount+1) g_strValue false
			format "[%,%,%,%]" tm._41 tm._42 tm._43 tm._44 to:m_fileTarget
			XMLElementEnd 0 g_strValue
		XMLElementEnd nTabCount g_strLocalTM
		
		StackClearAttr()
		XMLElementBegin nTabCount g_strWorldTM true
		tm = m_oUtil.ConvertToD3D_TM (obj.transform)
			XMLElementBegin (nTabCount+1) g_strValue false
			format "[%,%,%,%]" tm._11 tm._12 tm._13 tm._14 to:m_fileTarget
			XMLElementEnd 0 g_strValue
			XMLElementBegin (nTabCount+1) g_strValue false
			format "[%,%,%,%]" tm._21 tm._22 tm._23 tm._24 to:m_fileTarget
			XMLElementEnd 0 g_strValue
			XMLElementBegin (nTabCount+1) g_strValue false
			format "[%,%,%,%]" tm._31 tm._32 tm._33 tm._34 to:m_fileTarget
			XMLElementEnd 0 g_strValue
			XMLElementBegin (nTabCount+1) g_strValue false
			format "[%,%,%,%]" tm._41 tm._42 tm._43 tm._44 to:m_fileTarget
			XMLElementEnd 0 g_strValue
		XMLElementEnd nTabCount g_strWorldTM
	),

	fn WriteBoundingBox obj nTabCount =
	(
		StackClearAttr()
		XMLElementBegin nTabCount g_strBoundingBox true
		invTM = inverse (obj.transform)
			XMLElementBegin (nTabCount+1) g_strMax false
			format "%" (m_oUtil.ConvertToD3D_POS (obj.max * invTM)) to:m_fileTarget
			XMLElementEnd 0 g_strMax
			XMLElementBegin (nTabCount+1) g_strMin false
			format "%" (m_oUtil.ConvertToD3D_POS (obj.min * invTM)) to:m_fileTarget
			XMLElementEnd 0 g_strMin
			XMLElementBegin (nTabCount+1) g_strCenter false
			format "%" (m_oUtil.ConvertToD3D_POS (obj.center * invTM)) to:m_fileTarget
			XMLElementEnd 0 g_strCenter
		XMLElementEnd nTabCount g_strBoundingBox
	),
	
	fn WriteTriVertex obj nTabCount =
	(
		if superclassOf obj != GeometryClass then return undefined
		vertSet = #()
		
		vertSet = m_oUtil.GetLocalVertices obj
		
		StackClearAttr()
		XMLElementBegin nTabCount g_strTriVertex true
		for i = 1 to vertSet.count do
		(
			StackClearAttr()
			StackPushAttr g_strIndex (i - 1)
			XMLElementBegin (nTabCount+1) g_strValue false
			format "%" (m_oUtil.ConvertToD3D_POS vertSet[i]) to:m_fileTarget
			XMLElementEnd 0 g_strValue
		)
		XMLElementEnd nTabCount g_strTriVertex
	),

	fn WriteVertexNormal obj nTabCount =
	(
		if superclassOf obj != GeometryClass then return undefined
		vertSet = #()
		
		vertSet = m_oUtil.GetVertexNormals obj
		
		StackClearAttr()
		XMLElementBegin nTabCount g_strVertexNormal true
		for i = 1 to vertSet.count do
		(
			StackClearAttr()
			StackPushAttr g_strIndex (i - 1)
			XMLElementBegin (nTabCount+1) g_strValue false
			format "%" (m_oUtil.ConvertToD3D_POS vertSet[i]) to:m_fileTarget
			XMLElementEnd 0 g_strValue
		)
		XMLElementEnd nTabCount g_strVertexNormal
	),

	fn WriteTriIndex obj nTabCount =
	(
		if superclassOf obj != GeometryClass then return undefined
		
		fmSet = m_oUtil.SplitFacesByMaterial obj
		if fmSet == undefined then return undefined
		
		StackClearAttr()
		StackPushAttr g_strMtrlCount fmSet.count
		XMLElementBegin nTabCount g_strTriIndex true
		for i = 1 to fmSet.count do
		(
			StackClearAttr()
			StackPushAttr g_strMtrlID (fmSet[i].ID-1)
			for j = 1 to fmSet[i].faceSet.count do
			(
				XMLElementBegin (nTabCount+1) g_strValue false
				format "%" ( m_oUtil.ConvertToD3D_INDEX (getFace obj.mesh fmSet[i].faceSet[j]) ) to:m_fileTarget
				XMLElementEnd 0 g_strValue
			)
		)
		XMLElementEnd nTabCount g_strTriIndex
	),
	
	fn WriteTexVertex obj nTabCount =
	(
		if superclassOf obj != GeometryClass then return undefined
		if obj.mesh.numtverts == 0 do return undefined
		
		tvertCount = obj.mesh.numTVerts
		
		StackClearAttr()
		XMLElementBegin nTabCount g_strTexVertex true
		for i = 1 to tvertCount do
		(
			StackClearAttr()
			StackPushAttr g_strIndex (i - 1)
			XMLElementBegin (nTabCount+1) g_strValue false
			format "%" (m_oUtil.ConvertToD3D_UV (getTVert obj.mesh i)) to:m_fileTarget
			XMLElementEnd 0 g_strValue
		)
		XMLElementEnd nTabCount g_strTexVertex
	),
	
	fn WriteTexIndex obj nTabCount =
	(
		if superclassOf obj != GeometryClass then return undefined
		if obj.mesh.numtverts == 0 then return undefined

		fmSet = m_oUtil.SplitFacesByMaterial obj
		StackClearAttr()
		StackPushAttr g_strMtrlCount fmSet.count
		XMLElementBegin nTabCount g_strTexIndex true
		for i = 1 to fmSet.count do
		(
			StackClearAttr()
			StackPushAttr g_strMtrlID (fmSet[i].ID-1)
			for j = 1 to fmSet[i].faceSet.count do
			(
				XMLElementBegin (nTabCount+1) g_strValue false
				format "%" ( m_oUtil.ConvertToD3D_INDEX (getTVFace obj.mesh fmSet[i].faceSet[j]) ) to:m_fileTarget
				XMLElementEnd 0 g_strValue
			)
		)
		XMLElementEnd nTabCount g_strTexIndex
	),
	
	fn WriteKey obj nTabCount =
	(
		if (not obj.pos.isAnimated) and (not obj.rotation.isAnimated) and (not obj.scale.isAnimated) then return undefined
		
		StackClearAttr()
		
		XMLElementBegin nTabCount g_strKey true
		
		if obj.pos.isAnimated then
		(
			obj.pos.controller = tcb_position()
			local keys = obj.pos.controller.keys
			StackClearAttr()
			XMLElementBegin (nTabCount+1) g_strPosition true
			for i = 1 to keys.count do
			(
				StackClearAttr()
				StackPushAttr g_strFrameNo keys[i].time
				XMLElementBegin (nTabCount+2) g_strValue false
				format "%" (m_oUtil.ConvertToD3D_POS keys[i].value) to:m_fileTarget
				XMLElementEnd 0 g_strValue
			)
			XMLElementEnd (nTabCount+1) g_strPosition
		)
		
		if obj.rotation.isAnimated then
		(
			obj.rotation.controller = tcb_rotation()
			local keys = obj.rotation.controller.keys
			StackClearAttr()
			local MultQuat = quat 0 0 0 1 -- identity quaternion
			XMLElementBegin (nTabCount+1) g_strRotation true
			for i = 1 to keys.count do
			(
				StackClearAttr()
				StackPushAttr g_strFrameNo keys[i].time
				XMLElementBegin (nTabCount+2) g_strValue false
				local k = keys[i].value
				if i == 1 then k = (quat 0 0 0 1)
				if g_bMultiplyQuaternion then
				(
					MultQuat = MultQuat * k
				)
				else
				(
					MultQuat = k
				)
				q = (m_oUtil.ConvertToD3D_QUAT (MultQuat as quat))
				format "[%,%,%,%]" q.x q.y q.z q.w to:m_fileTarget
				XMLElementEnd 0 g_strValue
			)
			XMLElementEnd (nTabCount+1) g_strrotation
		)
		
		if obj.scale.isAnimated then
		(
			obj.scale.controller = tcb_scale()
			local keys = obj.scale.controller.keys
			StackClearAttr()
			XMLElementBegin (nTabCount+1) g_strScale true
			for i = 1 to keys.count do
			(
				StackClearAttr()
				StackPushAttr g_strFrameNo keys[i].time
				XMLElementBegin (nTabCount+2) g_strValue false
				format "%" (m_oUtil.ConvertToD3D_POS keys[i].value) to:m_fileTarget
				XMLElementEnd 0 g_strValue
			)
			XMLElementEnd (nTabCount+1) g_strScale
		)
		
		XMLElementEnd nTabCount g_strKey
	),
	
	fn WriteInfo nTabCount =
	(
		StackClearAttr()
		XMLElementBegin (nTabCount+1) g_strInfo true
			-- filename
			XMLElementBegin (nTabCount+2) g_strFilename false
			format "%" maxFileName to:m_fileTarget
			XMLElementEnd 0 g_strFilename
			-- ObjectCount
			XMLElementBegin (nTabCount+2) g_strObjectCount false
			format "%" objects.count to:m_fileTarget
			XMLElementEnd 0 g_strObjectCount
			-- MeshCount
			XMLElementBegin (nTabCount+2) g_strMeshCount false
			s = 0; for i = 1 to objects.count do ( if classOf objects[i] == Editable_mesh then s=s+1 )
			format "%" s to:m_fileTarget
			XMLElementEnd 0 g_strMeshCount
			-- Frame Rate
			XMLElementBegin (nTabCount+2) g_strFrameRate false
			format "%" frameRate to:m_fileTarget
			XMLElementEnd 0 g_strFrameRate
			-- Animation Start
			XMLElementBegin (nTabCount+2) g_strAniStart false
			format "%" animationRange.start to:m_fileTarget
			XMLElementEnd 0 g_strAniStart
			-- Animation End
			XMLElementBegin (nTabCount+2) g_strAniEnd false
			format "%" animationRange.end to:m_fileTarget
			XMLElementEnd 0 g_strAniEnd
			-- Animation Key type : KeyFrame, Sampling(ik,biped)
			XMLElementBegin (nTabCount+2) g_strTypeKey false
			format "%" g_strKeyType to:m_fileTarget
			XMLElementEnd 0 g_strTypeKey
			-- Object list
			StackClearAttr()
			XMLElementBegin (nTabCount+2) g_strObject true
			for i = 1 to m_oUtil.m_varSetObjectNames.count do
			(
				StackClearAttr()
				StackPushAttr g_strID (i - g_nObjectIDRef)
				XMLElementBegin (nTabCount+3) g_strValue false
				format "%" m_oUtil.m_varSetObjectNames[i] to:m_fileTarget
				XMLElementEnd 0 g_strValue
			)
			XMLElementEnd (nTabCount+2) g_strObject
			-- Bone list
			StackClearAttr()
			XMLElementBegin (nTabCount+2) g_strBone true
			for i = 1 to m_oUtil.m_varSetBoneNames.count do
			(
				StackClearAttr()
				StackPushAttr g_strBoneID (i-1)
				StackPushAttr g_strID (m_oUtil.GetObjectIDByName(m_oUtil.m_varSetBoneNames[i]) - g_nObjectIDRef)
				XMLElementBegin (nTabCount+3) g_strValue false
				format "%" m_oUtil.m_varSetBoneNames[i] to:m_fileTarget
				XMLElementEnd 0 g_strValue
			)
			XMLElementEnd (nTabCount+2) g_strBone

		XMLElementEnd (nTabCount+1) g_strInfo
	),
		
/*	fn WriteMaterial nTabCount =
	(
		StackClearAttr()
		XMLElementBegin (nTabCount+1) g_strMaterial true
		
		for i = 1 to m_oUtil.m_varSetMaterials.count do
		(
			StackClearAttr()
			StackPushAttr g_strIndex (i-1)
			XMLElementBegin (nTabCount+2) g_strSlot true
			StackClearAttr()
			-- Diffuse
				XMLElementBegin (nTabCount+3) g_strMtrlDiffuse false
				format "%" m_oUtil.m_varSetMaterials[i].Diffuse to:m_fileTarget
				XMLElementEnd 0 g_strMtrlDiffuse
			-- Ambient
				XMLElementBegin (nTabCount+3) g_strMtrlAmbient false
				format "%" m_oUtil.m_varSetMaterials[i].Ambient to:m_fileTarget
				XMLElementEnd 0 g_strMtrlAmbient
			-- Specular
				XMLElementBegin (nTabCount+3) g_strMtrlSpecular false
				format "%" m_oUtil.m_varSetMaterials[i].Specular to:m_fileTarget
				XMLElementEnd 0 g_strMtrlSpecular
			-- Emissive
				XMLElementBegin (nTabCount+3) g_strMtrlEmissive false
				format "%" m_oUtil.m_varSetMaterials[i].selfIllumColor to:m_fileTarget
				XMLElementEnd 0 g_strMtrlEmissive
			-- Opacity
				XMLElementBegin (nTabCount+3) g_strMtrlOpacity false
				format "%" m_oUtil.m_varSetMaterials[i].Opacity to:m_fileTarget
				XMLElementEnd 0 g_strMtrlOpacity				
			-- Power
				XMLElementBegin (nTabCount+3) g_strMtrlPower false
				format "%" m_oUtil.m_varSetMaterials[i].SpecularLevel to:m_fileTarget
				XMLElementEnd 0 g_strMtrlPower
			-- Diffuse Map
				if m_oUtil.m_varSetMaterials[i].DiffuseMap != undefined then
				(
					XMLElementBegin (nTabCount+3) g_strMtrlMapDiffuse false
					format "<![CDATA[%]]>" m_oUtil.m_varSetMaterials[i].DiffuseMap.filename to:m_fileTarget
					XMLElementEnd 0 g_strMtrlMapDiffuse
				)
			-- Specular Map
				if m_oUtil.m_varSetMaterials[i].SpecularMap != undefined  then
				(
					XMLElementBegin (nTabCount+3) g_strMtrlMapSpecualr false
					format "%" m_oUtil.m_varSetMaterials[i].SpecularMap.filename to:m_fileTarget
					XMLElementEnd 0 g_strMtrlMapSpecualr
				)
			-- Bump Map
				if m_oUtil.m_varSetMaterials[i].BumpMap != undefined  then
				(
					XMLElementBegin (nTabCount+3) g_strMtrlMapBump false
					format "%" m_oUtil.m_varSetMaterials[i].BumpMap.filename to:m_fileTarget
					XMLElementEnd 0 g_strMtrlMapBump
				)
			-- Displacement Map
				if m_oUtil.m_varSetMaterials[i].DisplacementMap != undefined  then
				(
					XMLElementBegin (nTabCount+3) g_strMtrlMapDisplace false
					format "%" m_oUtil.m_varSetMaterials[i].DisplacementMap.filename to:m_fileTarget
					XMLElementEnd 0 g_strMtrlMapDisplace
				)
			XMLElementEnd (nTabCount+2) g_strSlot
		)
		
		XMLElementEnd (nTabCount+1) g_strMaterial
	),
*/
	fn WriteControllerKeys ctrl nTabCount =
	(
		if( ctrl != undefined ) then
		(
			StackClearAttr()
			str = ctrl as string
			XMLElementBegin nTabCount "controller" true
			XMLElementBegin (nTabCount+1) "type" false; format "%" (substring str ((findstring str ":")+1) -1) to:m_fileTarget; XMLElementEnd 0 "type"
			for k in ctrl.keys do
			(
				StackClearAttr()
				StackPushAttr "time" k.time
				XMLElementBegin (nTabCount+1) "Key" false; format "%" k.value to:m_fileTarget; XMLElementEnd 0 "Key"
			)
			XMLElementEnd nTabCount "controller"
			StackClearAttr()
		)
	),
	
	fn WriteProperty o strProperty nTabCount =
	(
		val = getproperty o strProperty
		if( o == undefined ) then return undefined
		XMLElementBegin nTabCount strProperty true;
		XMLElementBegin (nTabCount+1) "value" false; format "%" val to:m_fileTarget; XMLElementEnd 0 "value"
		case ( strProperty ) of
		(
--			material properties
			"shaderType"			: WriteControllerKeys o.shaderType.controller (nTabCount+1)
			"wire"					: WriteControllerKeys o.wire.controller (nTabCount+1)
			"twoSided"				: WriteControllerKeys o.twoSided.controller (nTabCount+1)
			"faceMap"				: WriteControllerKeys o.faceMap.controller (nTabCount+1)
			"faceted"				: WriteControllerKeys o.faceted.controller (nTabCount+1)
			"shaderByName"			: WriteControllerKeys o.shaderByName.controller (nTabCount+1)
			"opacityType"			: WriteControllerKeys o.opacityType.controller (nTabCount+1)
			"opacity"				: WriteControllerKeys o.opacity.controller (nTabCount+1)
			"opacityFallOffType"	: WriteControllerKeys o.opacityFallOffType.controller (nTabCount+1)
			"opacityFallOff"		: WriteControllerKeys o.opacityFallOff.controller (nTabCount+1)
			"ior"					: WriteControllerKeys o.ior.controller (nTabCount+1)
			"wireSize"				: WriteControllerKeys o.wireSize.controller (nTabCount+1)
			"wireUnits"				: WriteControllerKeys o.wireUnits.controller (nTabCount+1)
			"applyReflectionDimming": WriteControllerKeys o.applyReflectionDimming.controller (nTabCount+1)
			"dimLevel"				: WriteControllerKeys o.dimLevel.controller (nTabCount+1)
			"reflectionLevel"		: WriteControllerKeys o.reflectionLevel.controller (nTabCount+1)
			"sampler"				: WriteControllerKeys o.sampler.controller (nTabCount+1)
			"samplerEnable"			: WriteControllerKeys o.samplerEnable.controller (nTabCount+1)
			"samplerAdaptThreshold"	: WriteControllerKeys o.samplerAdaptThreshold.controller (nTabCount+1)
			"samplerAdaptOn"		: WriteControllerKeys o.samplerAdaptOn.controller (nTabCount+1)
			"samplerAdvancedOptions": WriteControllerKeys o.samplerAdvancedOptions.controller (nTabCount+1)
			"samplerByName"			: WriteControllerKeys o.samplerByName.controller (nTabCount+1)
			"UserParam0"			: WriteControllerKeys o.UserParam0.controller (nTabCount+1)
			"UserParam1"			: WriteControllerKeys o.UserParam1.controller (nTabCount+1)
			"samplerUseGlobal"		: WriteControllerKeys o.samplerUseGlobal.controller (nTabCount+1)
			"subSampleTextureOn"	: WriteControllerKeys o.subSampleTextureOn.controller (nTabCount+1)
			"bounce"				: WriteControllerKeys o.bounce.controller (nTabCount+1)
			"staticFriction"		: WriteControllerKeys o.staticFriction.controller (nTabCount+1)
			"slidingFriction"		: WriteControllerKeys o.slidingFriction.controller (nTabCount+1)
			"ambient"				: WriteControllerKeys o.ambient.controller (nTabCount+1)
			"diffuse"				: WriteControllerKeys o.diffuse.controller (nTabCount+1)
			"specular"				: WriteControllerKeys o.specular.controller (nTabCount+1)
			"adTextureLock"			: WriteControllerKeys o.adTextureLock.controller (nTabCount+1)
			"adLock"				: WriteControllerKeys o.adLock.controller (nTabCount+1)
			"dsLock"				: WriteControllerKeys o.dsLock.controller (nTabCount+1)
			"useSelfIllumColor"		: WriteControllerKeys o.useSelfIllumColor.controller (nTabCount+1)
			"selfIllumAmount"		: WriteControllerKeys o.selfIllumAmount.controller (nTabCount+1)
			"selfIllumColor"		: WriteControllerKeys o.selfIllumColor.controller (nTabCount+1)
			"specularLevel"			: WriteControllerKeys o.specularLevel.controller (nTabCount+1)
			"glossiness"			: WriteControllerKeys o.glossiness.controller (nTabCount+1)
			"soften"				: WriteControllerKeys o.soften.controller (nTabCount+1)
			
--			material.map.coord properties
			"clipu"					: WriteControllerKeys o.clipu.controller (nTabCount+1)
			"clipv"					: WriteControllerKeys o.clipv.controller (nTabCount+1)
			"clipw"					: WriteControllerKeys o.clipw.controller (nTabCount+1)
			"cliph"					: WriteControllerKeys o.cliph.controller (nTabCount+1)
			"jitter"				: WriteControllerKeys o.jitter.controller (nTabCount+1)
			"useJitter"				: WriteControllerKeys o.useJitter.controller (nTabCount+1)
			"apply"					: WriteControllerKeys o.apply.controller (nTabCount+1)
			"cropPlace"				: WriteControllerKeys o.cropPlace.controller (nTabCount+1)
			"filtering"				: WriteControllerKeys o.filtering.controller (nTabCount+1)
			"monoOutput"			: WriteControllerKeys o.monoOutput.controller (nTabCount+1)
			"rgbOutput"				: WriteControllerKeys o.rgbOutput.controller (nTabCount+1)
			"alphaSource"			: WriteControllerKeys o.alphaSource.controller (nTabCount+1)
			"preMultAlpha"			: WriteControllerKeys o.preMultAlpha.controller (nTabCount+1)
			"fileName"				: WriteControllerKeys o.fileName.controller (nTabCount+1)
			"startTime"				: WriteControllerKeys o.startTime.controller (nTabCount+1)
			"playBackRate"			: WriteControllerKeys o.playBackRate.controller (nTabCount+1)
			"endCondition"			: WriteControllerKeys o.endCondition.controller (nTabCount+1)
			"tieTimeToMatIDs"		: WriteControllerKeys o.tieTimeToMatIDs.controller (nTabCount+1)

--			material.map.coord properties
			"blur" 					: WriteControllerKeys o.blur.controller (nTabCount+1)
			"mapping"				: WriteControllerKeys o.mapping.controller (nTabCount+1)
			"mapChannel"			: WriteControllerKeys o.mapChannel.controller (nTabCount+1)
			"mappingType"			: WriteControllerKeys o.mappingType.controller (nTabCount+1)
			"UVW_Type"				: WriteControllerKeys o.UVW_Type.controller (nTabCount+1)
			"U_Mirror"				: WriteControllerKeys o.U_Mirror.controller (nTabCount+1)
			"V_Mirror"				: WriteControllerKeys o.V_Mirror.controller (nTabCount+1)
			"U_Tile"				: WriteControllerKeys o.U_Tile.controller (nTabCount+1)
			"V_Tile"				: WriteControllerKeys o.V_Tile.controller (nTabCount+1)
			"showMapOnBack"			: WriteControllerKeys o.showMapOnBack.controller (nTabCount+1)
			"Noise_On"				: WriteControllerKeys o.Noise_On.controller (nTabCount+1)
			"Noise_Animate"			: WriteControllerKeys o.Noise_Animate.controller (nTabCount+1)
			"phase"					: WriteControllerKeys o.phase.controller (nTabCount+1)
			"U_Offset"				: WriteControllerKeys o.U_Offset.controller (nTabCount+1)
			"V_Offset"				: WriteControllerKeys o.V_Offset.controller (nTabCount+1)
			"U_Tiling"				: WriteControllerKeys o.U_Tiling.controller (nTabCount+1)
			"V_Tiling"				: WriteControllerKeys o.V_Tiling.controller (nTabCount+1)
			"U_Angle"				: WriteControllerKeys o.U_Angle.controller (nTabCount+1)
			"V_Angle"				: WriteControllerKeys o.V_Angle.controller (nTabCount+1)
			"W_Angle"				: WriteControllerKeys o.W_Angle.controller (nTabCount+1)
			"Noise_Amount"			: WriteControllerKeys o.Noise_Amount.controller (nTabCount+1)
			"Noise_Size"			: WriteControllerKeys o.Noise_Size.controller (nTabCount+1)
			"Noise_Levels"			: WriteControllerKeys o.Noise_Levels.controller (nTabCount+1)
			"Blur_Offset"			: WriteControllerKeys o.Blur_Offset.controller (nTabCount+1)
--			Camera properties
			"position"				: WriteControllerKeys o.position.controller (nTabCount+1)
			"fov"					: WriteControllerKeys o.fov.controller (nTabCount+1)
			"targetDistance"		: WriteControllerKeys o.targetDistance.controller (nTabCount+1)
			"nearrange"				: WriteControllerKeys o.nearrange.controller (nTabCount+1)
			"farrange"				: WriteControllerKeys o.farrange.controller (nTabCount+1)
			"nearclip"				: WriteControllerKeys o.nearclip.controller (nTabCount+1)
			"farclip"				: WriteControllerKeys o.farclip.controller (nTabCount+1)
		)
		XMLElementEnd nTabCount strProperty	
--		if( val.controller == undefined ) then WriteControllerKeys val.controller (nTabCount+1)
	),
	
	fn WriteProperties o nTabCount =
	(
		for i=1 to o.numSubs do
		(
			if ( o[i].numsubs == 0 ) then
			(
				if( o[i].value != undefined ) then
				(
					str = o[i] as string
					StackClearAttr()
					StackPushAttr "ID" (substring str ((findstring str ":")+1) -1)
					XMLElementBegin nTabCount "Property" true
						StackClearAttr()
						XMLElementBegin (nTabCount+1) "value" false; format "%" o[i].value to:m_fileTarget; XMLElementEnd 0 "value"
						if( o[i].value != undefined ) then WriteControllerKeys o[i].controller (nTabCount+1)
					XMLElementEnd nTabCount "Property"
				)
			)
			else
			(
				str = o[i] as string
				StackClearAttr()
				StackPushAttr "ID" (substring str ((findstring str ":")+1) -1)
				XMLElementBegin nTabCount "Property" true
					WriteProperties o[i] (nTabCount+1)
				XMLElementEnd nTabCount "Property"
			)
			
		)
	),

	fn WriteMaterial_Map_Coord coord nTabCount =
	(
		if ( coord == undefined ) then return undefined
		StackClearAttr()
		WriteProperty coord "blur" nTabCount
		WriteProperty coord "mapping" nTabCount
		WriteProperty coord "mapChannel" nTabCount
		WriteProperty coord "mappingType" nTabCount
		WriteProperty coord "UVW_Type" nTabCount
		WriteProperty coord "U_Mirror" nTabCount
		WriteProperty coord "V_Mirror" nTabCount
		WriteProperty coord "U_Tile" nTabCount
		WriteProperty coord "V_Tile" nTabCount
		WriteProperty coord "showMapOnBack" nTabCount
		WriteProperty coord "Noise_On" nTabCount
		WriteProperty coord "Noise_Animate" nTabCount
		WriteProperty coord "phase" nTabCount
		WriteProperty coord "U_Offset" nTabCount
		WriteProperty coord "V_Offset" nTabCount
		WriteProperty coord "U_Tiling" nTabCount
		WriteProperty coord "V_Tiling" nTabCount
		WriteProperty coord "U_Angle" nTabCount
		WriteProperty coord "V_Angle" nTabCount
		WriteProperty coord "W_Angle" nTabCount
		WriteProperty coord "Noise_Amount" nTabCount
		WriteProperty coord "Noise_Size" nTabCount
		WriteProperty coord "Noise_Levels" nTabCount
		WriteProperty coord "Blur_Offset" nTabCount
	),
	
	fn WriteMaterial_Map map map_enabled map_amount nTabCount =
	(
		if ( map == undefined ) then return undefined
		StackClearAttr()
		XMLElementBegin nTabCount "enabled" true; 
			XMLElementBegin (nTabCount+1) "value" false; format "%" map_enabled to:m_fileTarget; XMLElementEnd 0 "value"
		XMLElementEnd nTabCount "enabled"
			
		XMLElementBegin nTabCount "amount" true; 
			XMLElementBegin (nTabCount+1) "value" false; format "%" map_amount to:m_fileTarget; XMLElementEnd 0 "value"
		XMLElementEnd nTabCount "amount"
		
		WriteProperty map "clipu" nTabCount
		WriteProperty map "clipv" nTabCount
		WriteProperty map "clipw" nTabCount
		WriteProperty map "cliph" nTabCount
		WriteProperty map "jitter" nTabCount
		WriteProperty map "useJitter" nTabCount
		WriteProperty map "apply" nTabCount
		WriteProperty map "cropPlace" nTabCount
		WriteProperty map "filtering" nTabCount
		WriteProperty map "monoOutput" nTabCount
		WriteProperty map "rgbOutput" nTabCount
		WriteProperty map "alphaSource" nTabCount
		WriteProperty map "preMultAlpha" nTabCount
		XMLElementBegin nTabCount "coords" true
			WriteMaterial_Map_Coord map.coords (nTabCount+1)
		XMLElementEnd nTabCount "coords"
		WriteProperty map "fileName" nTabCount
		WriteProperty map "startTime" nTabCount
		WriteProperty map "playBackRate" nTabCount
		WriteProperty map "endCondition" nTabCount
		WriteProperty map "tieTimeToMatIDs" nTabCount
	),

	fn WriteMaterial o nTabCount =
	(
		if ( o == undefined ) then return undefined
		StackClearAttr()
		WriteProperty o "shaderType" nTabCount
		WriteProperty o "wire" nTabCount
		WriteProperty o "twoSided" nTabCount
		WriteProperty o "faceMap" nTabCount
		WriteProperty o "faceted" nTabCount
		WriteProperty o "shaderByName" nTabCount
		WriteProperty o "opacityType" nTabCount
		WriteProperty o "opacity" nTabCount
		WriteProperty o "opacityFallOffType" nTabCount
		WriteProperty o "opacityFallOff" nTabCount
		WriteProperty o "ior" nTabCount
		WriteProperty o "wireSize" nTabCount
		WriteProperty o "wireUnits" nTabCount
		WriteProperty o "applyReflectionDimming" nTabCount
		WriteProperty o "dimLevel" nTabCount
		WriteProperty o "reflectionLevel" nTabCount
		WriteProperty o "sampler" nTabCount
		WriteProperty o "samplerEnable" nTabCount
		WriteProperty o "samplerAdaptThreshold" nTabCount
		WriteProperty o "samplerAdaptOn" nTabCount
		WriteProperty o "samplerAdvancedOptions" nTabCount
		WriteProperty o "samplerByName" nTabCount
		WriteProperty o "UserParam0" nTabCount
		WriteProperty o "UserParam1" nTabCount
		WriteProperty o "samplerUseGlobal" nTabCount
		WriteProperty o "subSampleTextureOn" nTabCount
		XMLElementBegin nTabCount "Map" true
		for i = 1 to o.Maps.count do
		(
			WriteMaterial_Map o.maps[i] o.mapEnables[i] o.mapAmounts[i] (nTabCount+1)
		)
		XMLElementEnd nTabCount "Map"
		WriteProperty o "bounce" nTabCount
		WriteProperty o "staticFriction" nTabCount
		WriteProperty o "slidingFriction" nTabCount
		WriteProperty o "ambient" nTabCount
		WriteProperty o "diffuse" nTabCount
		WriteProperty o "specular" nTabCount
		WriteProperty o "adTextureLock" nTabCount
		WriteProperty o "adLock" nTabCount
		WriteProperty o "dsLock" nTabCount
		WriteProperty o "useSelfIllumColor" nTabCount
		WriteProperty o "selfIllumAmount" nTabCount
		WriteProperty o "selfIllumColor" nTabCount
		WriteProperty o "specularLevel" nTabCount
		WriteProperty o "glossiness" nTabCount
		WriteProperty o "soften" nTabCount
	),
		
	fn WriteMaterials nTabCount =
	(
		StackClearAttr()
		XMLElementBegin nTabCount "Materials" true
		for i=1 to m_oUtil.m_varSetMaterials.count do
		(
			StackClearAttr()
			StackPushAttr "Index" (i-1)
			XMLElementBegin (nTabCount+1) "Slot" true
				WriteMaterial m_oUtil.m_varSetMaterials[i] (nTabCount+2)
--				WriteProperties m_oUtil.m_varSetMaterials[i] (nTabCount+2)
			XMLElementEnd (nTabCount+1) "Slot"
		)
		XMLElementEnd nTabCount "Materials"
	),
	
	fn WriteVertexWeight obj nTabCount =
	(
		ret = undefined
		if obj.modifiers[#skin] != undefined then ret = m_oUtil.GetVertexWeightsBySkin obj
		if obj.modifiers[#physique] != undefined then ret = m_oUtil.GetVertexWeightsByPhysique obj
		if undefined == ret then return undefined
		
		StackClearAttr()
		StackPushAttr g_strBoneCount ret.nBoneCount
		XMLElementBegin nTabCount g_strVertexWeight true
		for i = 1 to ret.VertexSet.Count do
		(
			StackClearAttr()
			StackPushAttr g_strIndex (i-1)
			XMLElementBegin (nTabCount+1) g_strTriVertex true
			vs = ret.VertexSet[i]
			mysort vs (fn compare v1 v2 = (v2.weight - v1.weight))
			for j = 1 to vs.count do
			(
				StackClearAttr()
				StackPushAttr g_strBoneID (m_oUtil.GetBoneIDByName vs[j].strName)
				if g_bObjectIDWithName then StackPushAttr g_strName vs[j].strName
				XMLElementBegin (nTabCount+2) g_strValue false
				format "%" vs[j].weight to:m_fileTarget
				XMLElementEnd 0 g_strValue
			)
			XMLElementEnd (nTabCount+1) g_strTriVertex
		)		
		XMLElementEnd nTabCount g_strVertexWeight
	),
			
	fn WriteObject obj nTabCount =
	(
		bNeedUndo = false
		if classof obj == TargetCamera then return undefined
		if classof obj == TargetObject then return undefined
		if classof obj == FreeCamera then return undefined
		if obj == undefined then return undefined
--		if (canConvertTo obj Editable_mesh) == true then
		(
--			undo on
			(
--				if (classof obj) != Editbale_mesh then ( convertToMesh obj; bNeedUndo = true )
				StackClearAttr()
				StackPushAttr g_strID ((m_oUtil.GetObjectID obj) - g_nObjectIDRef)
				if g_bObjectIDWithName then StackPushAttr g_strName (obj.name)
				StackPushAttr g_strClass (classOf obj as string)
				XMLElementBegin nTabCount g_strObject true
					WriteParent obj (nTabCount+1)
					WriteTM obj (nTabCount+1)
					WriteBoundingBox obj (nTabCount+1)
					WriteTriVertex obj (nTabCount+1)
					WriteVertexNormal obj (nTabCount+1)
					WriteTriIndex obj (nTabCount+1)
					WriteTexVertex obj (nTabCount+1)
					WriteTexIndex obj (nTabCount+1)
					WriteVertexWeight obj (nTabCount+1)
					if g_bSampling then 
					(
						o = FindObject (obj.name + "_snap")
						if o != undefined then
						(
							format "%:%\n" obj.name o.name
							WriteKey o (nTabCount+1)
						)
						
					)
					else
					(
						WriteKey obj (nTabCount+1)
					)
				XMLElementEnd nTabCount g_strObject
			)
--			if bNeedUndo == true then max undo
		)
	),

	fn WriteCameraProperty_TargetCamera c nTabCount =
	(
		XMLElementBegin nTabCount "TargetCamera" true
			WriteProperty c "name" (nTabCount+1)
			XMLElementBegin (nTabCount+1) "type" false; format "%" "TargetCamera" to:m_fileTarget; XMLElementEnd 0 "type"
			WriteProperty c "position" (nTabCount+1)
			WriteProperty c "fov" (nTabCount+1)
			WriteProperty c "nearrange" (nTabCount+1)
			WriteProperty c "farrange" (nTabCount+1)
			WriteProperty c "nearclip" (nTabCount+1)
			WriteProperty c "farclip" (nTabCount+1)
			WriteProperty c "mpassEnabled" (nTabCount+1)
			WriteProperty c "mpassRenderPerPass" (nTabCount+1)
			WriteProperty c "orthoProjection" (nTabCount+1)
			WriteProperty c "showCone" (nTabCount+1)
			WriteProperty c "showHorizon" (nTabCount+1)
			WriteProperty c "clipManually" (nTabCount+1)
			WriteProperty c "mpassEffect" (nTabCount+1)
			WriteProperty c "multipass_effect" (nTabCount+1)
/*			
			XMLElementBegin (nTabCount+1) "name" false; format "%" c.name to:m_fileTarget; XMLElementEnd 0 "name"
			XMLElementBegin (nTabCount+1) "type" false; format "%" "TargetCamera" to:m_fileTarget; XMLElementEnd 0 "type"
			XMLElementBegin (nTabCount+1) "position" false; format "%" c.pos to:m_fileTarget; XMLElementEnd 0 "position"
			XMLElementBegin (nTabCount+1) "fov" false; format "%" c.fov to:m_fileTarget; XMLElementEnd 0 "fov"
			XMLElementBegin (nTabCount+1) "nearrange" false; format "%" c.nearrange to:m_fileTarget; XMLElementEnd 0 "nearrange"
			XMLElementBegin (nTabCount+1) "farrange" false; format "%" c.farrange to:m_fileTarget; XMLElementEnd 0 "farrange"
			XMLElementBegin (nTabCount+1) "nearclip" false; format "%" c.nearclip to:m_fileTarget; XMLElementEnd 0 "nearclip"
			XMLElementBegin (nTabCount+1) "farclip" false; format "%" c.farclip to:m_fileTarget; XMLElementEnd 0 "farclip"
			XMLElementBegin (nTabCount+1) "mpassEnabled" false; format "%" c.mpassEnabled to:m_fileTarget; XMLElementEnd 0 "mpassEnabled"
			XMLElementBegin (nTabCount+1) "mpassRenderPerPass" false; format "%" c.mpassRenderPerPass to:m_fileTarget; XMLElementEnd 0 "mpassRenderPerPass"
			XMLElementBegin (nTabCount+1) "orthoProjection" false; format "%" c.orthoProjection to:m_fileTarget; XMLElementEnd 0 "orthoProjection"
			XMLElementBegin (nTabCount+1) "showCone" false; format "%" c.showCone to:m_fileTarget; XMLElementEnd 0 "showCone"
			XMLElementBegin (nTabCount+1) "showHorizon" false; format "%" c.showHorizon to:m_fileTarget; XMLElementEnd 0 "showHorizon"
			XMLElementBegin (nTabCount+1) "clipManually" false; format "%" c.clipManually to:m_fileTarget; XMLElementEnd 0 "clipManually"
			XMLElementBegin (nTabCount+1) "mpassEffect" false; format "%" c.mpassEffect to:m_fileTarget; XMLElementEnd 0 "mpassEffect"
			XMLElementBegin (nTabCount+1) "multipass_effect" false; format "%" c.multipass_effect to:m_fileTarget; XMLElementEnd 0 "multipass_effect"
*/			
			WriteTM c nTabCount
		XMLElementEnd nTabCount "TargetCamera"
	),
	
	fn WriteCameraProperty_Target c nTabCount=
	(
		XMLElementBegin nTabCount "TargetObject" true
			WriteProperty c "name" (nTabCount+1)
			XMLElementBegin (nTabCount+1) "type" false; format "%" "TargetObject" to:m_fileTarget; XMLElementEnd 0 "type"
			WriteProperty c "position" (nTabCount+1)
--			XMLElementBegin (nTabCount+1) "name" false; format "%" c.name to:m_fileTarget; XMLElementEnd 0 "name"
--			XMLElementBegin (nTabCount+1) "type" false; format "%" "TargetObject" to:m_fileTarget; XMLElementEnd 0 "type"
--			XMLElementBegin (nTabCount+1) "position" false; format "%" c.pos to:m_fileTarget; XMLElementEnd 0 "position"
			WriteTM c nTabCount
		XMLElementEnd nTabCount "TargetObject"
	),
	
	fn WriteCameraProperty_FreeCamera c nTabCount=
	(
		XMLElementBegin nTabCount "FreeCamera" true
			WriteProperty c "name" (nTabCount+1)
			XMLElementBegin (nTabCount+1) "type" false; format "%" "FreeCamera" to:m_fileTarget; XMLElementEnd 0 "type"
			WriteProperty c "position" (nTabCount+1)
			WriteProperty c "fov" (nTabCount+1)
			WriteProperty c "targetDistance" (nTabCount+1)
			WriteProperty c "nearrange" (nTabCount+1)
			WriteProperty c "farrange" (nTabCount+1)
			WriteProperty c "nearclip" (nTabCount+1)
			WriteProperty c "farclip" (nTabCount+1)
			WriteProperty c "mpassEnabled" (nTabCount+1)
			WriteProperty c "mpassRenderPerPass" (nTabCount+1)
			WriteProperty c "orthoProjection" (nTabCount+1)
			WriteProperty c "showCone" (nTabCount+1)
			WriteProperty c "showHorizon" (nTabCount+1)
			WriteProperty c "clipManually" (nTabCount+1)
			WriteProperty c "mpassEffect" (nTabCount+1)
			WriteProperty c "multipass_effect" (nTabCount+1)
/*			
			XMLElementBegin (nTabCount+1) "name" false; format "%" c.name to:m_fileTarget; XMLElementEnd 0 "name"
			XMLElementBegin (nTabCount+1) "type" false; format "%" "FreeCamera" to:m_fileTarget; XMLElementEnd 0 "type"
			XMLElementBegin (nTabCount+1) "position" false; format "%" c.pos to:m_fileTarget; XMLElementEnd 0 "position"
			XMLElementBegin (nTabCount+1) "fov" false; format "%" c.fov to:m_fileTarget; XMLElementEnd 0 "fov"
			XMLElementBegin (nTabCount+1) "targetDistance" false; format "%" c.targetDistance to:m_fileTarget; XMLElementEnd 0 "targetDistance"
			XMLElementBegin (nTabCount+1) "nearrange" false; format "%" c.nearrange to:m_fileTarget; XMLElementEnd 0 "nearrange"
			XMLElementBegin (nTabCount+1) "farrange" false; format "%" c.farrange to:m_fileTarget; XMLElementEnd 0 "farrange"
			XMLElementBegin (nTabCount+1) "nearclip" false; format "%" c.nearclip to:m_fileTarget; XMLElementEnd 0 "nearclip"
			XMLElementBegin (nTabCount+1) "farclip" false; format "%" c.farclip to:m_fileTarget; XMLElementEnd 0 "farclip"
			XMLElementBegin (nTabCount+1) "mpassEnabled" false; format "%" c.mpassEnabled to:m_fileTarget; XMLElementEnd 0 "mpassEnabled"
			XMLElementBegin (nTabCount+1) "mpassRenderPerPass" false; format "%" c.mpassRenderPerPass to:m_fileTarget; XMLElementEnd 0 "mpassRenderPerPass"
			XMLElementBegin (nTabCount+1) "orthoProjection" false; format "%" c.orthoProjection to:m_fileTarget; XMLElementEnd 0 "orthoProjection"
			XMLElementBegin (nTabCount+1) "showCone" false; format "%" c.showCone to:m_fileTarget; XMLElementEnd 0 "showCone"
			XMLElementBegin (nTabCount+1) "showHorizon" false; format "%" c.showHorizon to:m_fileTarget; XMLElementEnd 0 "showHorizon"
			XMLElementBegin (nTabCount+1) "clipManually" false; format "%" c.clipManually to:m_fileTarget; XMLElementEnd 0 "clipManually"
			XMLElementBegin (nTabCount+1) "mpassEffect" false; format "%" c.mpassEffect to:m_fileTarget; XMLElementEnd 0 "mpassEffect"
			XMLElementBegin (nTabCount+1) "multipass_effect" false; format "%" c.multipass_effect to:m_fileTarget; XMLElementEnd 0 "multipass_effect"
*/			
			WriteTM c nTabCount
		XMLElementEnd nTabCount "FreeCamera"
	),

	fn WriteCamera nTabCount =
	(
		StackClearAttr()
		XMLElementBegin nTabCount "Cameras" true
		for c in cameras do
		(
			if (isProperty c "position") == true then
			(
				if (classof c.position.controller) == Position_XYZ then c.position.controller = Bezier_Position()
			)

			if (isProperty c "rotation") == true then
			(
				if (classof c.rotation.controller) == Euler_XYZ then c.rotation.controller = Bezier_Rotation()
			)

			if (isProperty c "scale") == true then
			(
				if (classof c.scale.controller) == ScaleXYZ then c.scale.controller = Bezier_Scale()
			)
			
			case (classof c) of
			(
				TargetCamera : WriteCameraProperty_TargetCamera c (nTabCount+1)
				TargetObject : WriteCameraProperty_Target c (nTabCount+1)
				FreeCamera   : WriteCameraProperty_FreeCamera c (nTabCount+1)
			)	
		)
		
		XMLElementEnd nTabCount "Cameras"
	),
	
	fn Main =
	(
		StackClearAttr()
		format "<?xml version=\"1.0\" encoding=\"euc-kr\"?>\n" to:m_fileTarget
		XMLElementBegin 1 g_strBody true
		if g_bSampling then
		(
			m_oUtil.DumpObjects Biped_Object
			m_oUtil.DumpObjects BoneGeometry
			m_oUtil.DumpObjects Bone
			m_oUtil.DumpObjects helper
		)
			WriteInfo 1
--			WriteMaterial 1
			WriteMaterials 1
			WriteCamera 2
			for i = 1 to m_oUtil.m_varSetObjectNames.count do
			(
				g_uiObjectName.text = m_oUtil.m_varSetObjectNames[i]
				g_uiProgress.value = 100.*i/m_oUtil.m_varSetObjectNames.count
				WriteObject (FindObject m_oUtil.m_varSetObjectNames[i]) 2
			)
		if $ != undefined then deselect $
		select $'*snap'
		delete selection
		g_snapObjects  = undefined
		XMLElementEnd 1 g_strBody
	)
)

utility NewtypeExporter "Newtype Exporter" width:162 height:334
(
	local strFilename = "default.xml"
	local strViewPath = "*.exe"
	
	checkbox chkObjectIDWithName "ID와 Text함께 출력" pos:[8,48] width:116 height:17
	GroupBox grp3 "출력형식" pos:[4,32] width:154 height:83
	checkbox chkMultiplyQuaternion "Quaternion값 누적" pos:[8,80] width:122 height:17 enabled:false checked:false
	edittext editPathName "" pos:[3,10] width:151 height:17 enabled:true
	button btnPathName "..." pos:[71,155] width:47 height:17
	button btnRun "데이터생성" pos:[6,222] width:152 height:20
	label lbl2 "3dstudy.net" pos:[89,312] width:67 height:17
	checkbox chkWriteToDebug "Debug창 출력" pos:[8,64] width:107 height:17
	label lbl4 "출력파일명:" pos:[7,156] width:63 height:17
	checkbox chkSampling "샘플링(Biped,IK는  필수)" pos:[8,95] width:144 height:17 enabled:true
	progressBar pb1 "" pos:[5,203] width:154 height:16
	label lbl17 "처리중 :" pos:[7,188] width:46 height:15
	label lblObjectName "" pos:[52,188] width:105 height:15
	spinner spnSamplingGap "" pos:[70,132] width:49 height:16 enabled:false range:[1,100,0] type:#integer scale:1 value:1
	label lbl39 "샘플링간격:" pos:[7,133] width:63 height:17
	GroupBox grp4 "특성값" pos:[5,116] width:153 height:69
	
	edittext edtViewerLocation "" pos:[3,264] width:93 height:17 enabled:true
	button btnLocateViewer "뷰어위치" pos:[102,264] width:56 height:17
	GroupBox grp8 "미리보기" pos:[1,247] width:161 height:60
	button btnPreview "미리보기" pos:[6,284] width:152 height:20
	on chkObjectIDWithName changed state do
	(
		g_bObjectIDWithName = state
	)
	on chkMultiplyQuaternion changed state do
	(
		g_bMultiplyQuaternion = state
	)
	on btnPathName pressed do
	(
	    temp = getSaveFileName filename:strFilename types:"XML(*.xml)|*.xml|All|*.*|"
	    if temp != undefined then editPathName.text = temp
	)
	on btnRun pressed do
	(
		g_uiObjectName = lblObjectName
		g_uiProgress = pb1
		if spnSamplingGap.value < 1 then spnSamplingGap.value = 1
		g_nSampling = spnSamplingGap.value
		if editPathName.text == "" then editPathName.text = "default.xml"
	    strFilename = editPathName.text
		oExport = ZExport 0 strFilename 0 #() #()
		oExport.Constructor()						-- 생성자. 반드시 호출해줘야 한다.
		oExport.Main()								-- 메인함수.
		oExport.Destructor()						-- 소멸자. 반드시 호출해줘야 한다.
		gc()
	)
	on chkWriteToDebug changed state do
	(
		if state then
		(
			editPathName.text = "debug"
			editPathName.enabled = false
			btnPathName.enabled = false
		)
		else
		(
			editPathName.enabled = true
			btnPathName.enabled = true
		)
	)
	on chkSampling changed state do
	(
		g_bSampling = state
		spnSamplingGap.enabled = state
		if g_bSampling then
		(
			g_strKeyType = "Sampling"
		)
		else
		(
			g_strKeyType = "Keyframe"
		)
	
	)
	on btnLocateViewer pressed do
	(
	    temp = getOpenFileName filename:"*.exe" types:"exe(*.exe)|All|*.*|"
	    if temp != undefined then edtViewerLocation.text = temp
	)
	on btnPreview pressed do
	(
--		ShellLaunch strViewPath strFilename
		if edtViewerLocation.text == "" then ( messageBox "뷰어의 위치를 정해 주십시오" title:"심각한 오류" )
		else if editPathName.text == "" then ( messageBox "생성할 파일명을 먼저 정하세요" title:"심각한 오류" )
		else ( ShellLaunch edtViewerLocation.text editPathName.text )
	)
)

-- Material Editor에서 EffectMaterial이라는 새로운 Standard확장 Material추가
-- DirectX의 텍스처 스테이지 블렌딩 옵션값들 설정용
plugin material Kocca_EffectMaterial
name:"Effect Material"
classID:#(0x4d705c7d, 0x5f12aebf)
extends:Standard replaceUI:false
( 
	parameters main rollout:params
	(
	)
	
	rollout params "Effect Parameters" width:326 height:244
	(
		GroupBox grp1 "Blend Mode" pos:[2,-1] width:160 height:86
		label lbl1 "SRC:" pos:[17,23] width:26 height:13
		label lbl2 "DST:" pos:[17,54] width:27 height:13
		dropdownList ddlBlendSrc "" pos:[46,20] width:94 height:21 items:#("ONE", "ZERO", "SRCCOLOR", "INVSRCCOLOR", "DESTCOLOR", "INVDESTCOLOR", "SRCALPHA", "INVSRCALPHA", "DESTALPHA", "INVDESTALPHA", "SRCALPHASAT")
		dropdownList ddlBlendDst "" pos:[46,51] width:94 height:21 items:#("ONE", "ZERO", "SRCCOLOR", "INVSRCCOLOR", "DESTCOLOR", "INVDESTCOLOR", "SRCALPHA", "INVSRCALPHA", "DESTALPHA", "INVDESTALPHA", "SRCALPHASAT")
		GroupBox grp2 "Alpha Testing" pos:[165,0] width:157 height:85
		checkbox chk1 "On" pos:[171,14] width:39 height:17
		spinner spn1 "" pos:[271,14] width:43 height:16 range:[0,255,0] type:#integer scale:1
		label lbl3 "Test Ref:" pos:[226,15] width:46 height:15
		dropdownList ddl3 "Test Mode" pos:[206,37] width:80 height:40 items:#("ALWAYS", "LESS", "EQUAL", "LESSEQUAL", "GREATER", "NOEQUAL", "GREATEREQUAL", "NEVER")
		GroupBox grp3 "Custom Shader" pos:[2,94] width:320 height:143
		dropdownList ddlWhichShader "" pos:[82,115] width:174 height:21 items:#("Alpah Texture Blender", "Anisotropic", "Colorize", "Default Shader", "Dot3Bump", "기타등등")
		label lbl4 "셰이더:" pos:[33,117] width:44 height:18
		label lbl5 "설명 :" pos:[42,142] width:33 height:15
		button btnApplyShader "적용" pos:[83,203] width:169 height:26
		edittext edtShaderDescription "" pos:[77,143] width:178 height:51
	)	on create do
	(
		-- setup initial material
	)
)
