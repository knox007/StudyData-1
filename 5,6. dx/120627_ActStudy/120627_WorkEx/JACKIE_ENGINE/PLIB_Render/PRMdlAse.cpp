#include "StdAfx.h"
#include ".\prmdlase.h"
#include "PUtCommon.h"
#include "PRAseCommon.h"
#include "PUtCommonFPath.h"
#include "PUtCommonStr.h"
#include "PRCommonFunc.h"
#include "PUTCommonVerIntegrate.h"
#include "PRCommonFunc.h"

const int		MAX_PARSE_LINE	=	512;
const TCHAR*	FILE_TXT		=	PUT_CSTR_TCHAR(".txt");
//----------------------------------------------------------------------------------------
void	CPRMdlAse::InitMembers()
{
	PUT_ZERO_MEMORY( m_tszFile );
	PUT_ZERO_MEMORY( m_tszConfirmFile );
	
	m_nTotGeom	=	0;
	m_pGeomArr	=	NULL;

	m_nTotMtrl	=	0;
	m_pMtrlArr	=	NULL;

	m_pDev		=	NULL;

}//	InitMembers
//----------------------------------------------------------------------------------------
void	CPRMdlAse::ClearMembers()
{
	PUT_SAFE_DELETE_ARRAY( m_pGeomArr );
	PUT_SAFE_DELETE_ARRAY( m_pMtrlArr );

}//	ClearMembers
//----------------------------------------------------------------------------------------
bool	CPRMdlAse::CreateVtx( LPDIRECT3DDEVICE9 pDev )
{
	bool bRes = true;
	int nCur = 0;
	PUT_FOR( nCur, 0, m_nTotGeom )
	{
		bRes = m_pGeomArr[nCur].CreateVtx( m_pDev );
		if( !bRes )
			return false;
	}	

	return true;

}//	CreateVtx 
//----------------------------------------------------------------------------------------
bool CPRMdlAse::CreateIdx( LPDIRECT3DDEVICE9 pDev )
{
	bool bRes = true;
	int nCur = 0;
	PUT_FOR( nCur, 0, m_nTotGeom )
	{
		bRes = m_pGeomArr[nCur].CreateIdx( m_pDev );
		if( !bRes )
			return false;
	}

	return true;

}//	CreateIdx
//----------------------------------------------------------------------------------------
bool	CPRMdlAse::CreateTexture( LPDIRECT3DDEVICE9 pDev, TCHAR* ptszTxtrPath )
{
	int nCurMtrlIdx = 0;
	PUT_FOR( nCurMtrlIdx, 0, m_nTotMtrl )
	{
		SPRAseMtrl* pCurMtrl	=	&m_pMtrlArr[nCurMtrlIdx];

		if( strlen( pCurMtrl->_tszTxtrName) )
		{
			TCHAR	tszFile[MAX_PATH]	=	{0,};

			DWORD		dwColor		=	0x00ffffff;
			DWORD		dwFilter	=	( D3DX_FILTER_TRIANGLE | D3DX_FILTER_MIRROR );
			DWORD		dwMipFilter	=	( D3DX_FILTER_TRIANGLE | D3DX_FILTER_MIRROR );
			D3DFORMAT	d3dFormat	=	D3DFMT_UNKNOWN;

			PUT_Sprintf( tszFile, "%s%s", ptszTxtrPath, pCurMtrl->_tszTxtrName );

			if( FAILED( devCreateTxtrFromFileEx(	pDev,
													tszFile,
													D3DX_DEFAULT,
													D3DX_DEFAULT,
													D3DX_DEFAULT,
													0,
													d3dFormat,
													D3DPOOL_MANAGED,
													dwFilter,
													dwMipFilter,
													dwColor,
													&pCurMtrl->_ImgInfo,
													NULL,
													&pCurMtrl->_pD3dTxtr ) ) )
			{
				PUT_ERROR;
				return false;
			}
		}
	}
	
	return true;

}//	CreateTexture
//----------------------------------------------------------------------------------------
bool	CPRMdlAse::Confirm( TCHAR* tszConfirmFName )
{
	FILE*	fp = NULL;
	INT		i=0, j=0;

	PUT_ChangeExt( m_tszFile, m_tszConfirmFile, FILE_TXT );

	PUT_FOpen( &fp, m_tszConfirmFile, "wt");

	if(NULL == fp)
		return false;


	for(i=0; i<m_nTotGeom; ++i)
	{
		fprintf(fp, "%s__%d\n", g_ConfirmAseKey[eASEKEY_GEOMOBJECT]._tszAseKeyword, i );
		fprintf(fp, "	%s	\"%s\"\n", g_ConfirmAseKey[eASEKEY_NODE_NAME]._tszAseKeyword, m_pGeomArr[i].GetNodeName());
		fprintf(fp, "	%s\n", g_ConfirmAseKey[eASEKEY_MESH]._tszAseKeyword);

		fprintf(fp, "		%s	%d\n", g_ConfirmAseKey[eASEKEY_MESH_NUMVERTEX]._tszAseKeyword, m_pGeomArr[i].GetTotVtxCnt());
		fprintf(fp, "		%s	%d\n", g_ConfirmAseKey[eASEKEY_MESH_NUMFACES]._tszAseKeyword, m_pGeomArr[i].GetTotIdxCnt());

		fprintf(fp, "		%s\n"	, g_ConfirmAseKey[eASEKEY_MESH_VERTEX_LIST]._tszAseKeyword);

		int iNumVtx = m_pGeomArr[i].GetTotVtxCnt();

		for(j=0; j<iNumVtx; ++j)
			fprintf(fp, "			%s__%d\t\tX_ %f	Y_ %f	Z_ %f\n", g_ConfirmAseKey[eASEKEY_MESH_VERTEX]._tszAseKeyword
			,j
			, m_pGeomArr[i].GetVtx(j)._fX
			, m_pGeomArr[i].GetVtx(j)._fY
			, m_pGeomArr[i].GetVtx(j)._fZ);

		fprintf(fp, "		}\n\n");

		fprintf(fp, "		%s\n"	, g_ConfirmAseKey[eASEKEY_MESH_FACE_LIST]._tszAseKeyword);

		int iNumFce = m_pGeomArr[i].GetTotIdxCnt();

		for(j=0; j<iNumFce; ++j)
			fprintf(fp, "			%s__%d\t\tA_ %u	B_ %u	C_ %u\n", g_ConfirmAseKey[eASEKEY_MESH_FACE]._tszAseKeyword
			, j
			, m_pGeomArr[i].GetIdx3D(j)._wA
			, m_pGeomArr[i].GetIdx3D(j)._wB
			, m_pGeomArr[i].GetIdx3D(j)._wC );

		fprintf(fp, "		}\n");

		fprintf(fp, "	}\n");

		fprintf(fp, "}\n");
	}

	fclose(fp);



	return true;

}//	Confirm
//----------------------------------------------------------------------------------------
bool	CPRMdlAse::Load()
{
	FILE*	fp = NULL;
	char	sLine[MAX_PARSE_LINE];

	PUT_FOpen( &fp, m_tszFile, "rt" );
	if(NULL == fp)
		return false;

	m_nTotMtrl = 0;

	while( !feof(fp) )
	{
		PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );

		if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MATERIAL_LIST]._tszAseKeyword ) )
		{
			while( !feof(fp) )
			{
				PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );

				if('}' == sLine[0])
					break;

				if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MATERIAL_COUNT]._tszAseKeyword ) )
				{
					int nMtrlCount = 0;
					sscanf( sLine, "%*s %d", &nMtrlCount );
					m_nTotMtrl = nMtrlCount;

					if( m_nTotMtrl > 0 )
						m_pMtrlArr = new SPRAseMtrl[m_nTotMtrl];

				}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MATERIAL_COUNT]._tszAseKeyword ) )


				if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MATERIAL]._tszAseKeyword ) )
				{
					int nMtrl = -1;
					sscanf( sLine, "%*s %d", &nMtrl );

					while( !feof(fp) )
					{
						PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );

						if('}' == sLine[0])
							break;

						if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MAP_DIFFUSE]._tszAseKeyword ) )
						{
							while( !feof(fp) )
							{
								PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );

								if('}' == sLine[0])
									break;

								if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_BITMAP]._tszAseKeyword ) )
								{
									char	sFile[512];
									PUT_GetStrInQuot(sFile, sLine);

									char sTx[_MAX_FNAME]={0};
									char dir[_MAX_DIR]={0};
									char ext[_MAX_EXT];

									_splitpath (sFile, NULL, dir, sTx, ext);

									sprintf(m_pMtrlArr[nMtrl]._tszTxtrName, "%s%s", sTx, ext);

								}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_BITMAP]._tszAseKeyword ) )

							}//	while( !feof(fp) )

						}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MAP_DIFFUSE]._tszAseKeyword ) )

					}//	while( !feof(fp) )

				}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MATERIAL]._tszAseKeyword ) )

			}//	while( !feof(fp) )

		}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MATERIAL_LIST]._tszAseKeyword ) )

	}//	while( !feof(fp) )
    
	// 파일 포인터를 처음으로 옮긴다.
	fseek(fp, 0, SEEK_SET);

	//일단 Geometry가 하나만 있다고 가정하자.
	m_nTotGeom	= 0;

	while(!feof(fp))
	{
		PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );

		if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_GEOMOBJECT]._tszAseKeyword ) )
			++m_nTotGeom;
	}

	if(0==m_nTotGeom)
	{
		fclose(fp);
		return false;
	}

	// 파일 포인터를 처음으로 옮긴다.
	fseek(fp, 0, SEEK_SET);

	m_pGeomArr = new CPRAseGeom[m_nTotGeom];	
	CPRAseGeom* pCurGeom = NULL;
	int nGeoIdx = -1;

	while(!feof(fp))
	{
		PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );

		if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_GEOMOBJECT]._tszAseKeyword ) )
		{
			++nGeoIdx;
			pCurGeom	=	&m_pGeomArr[nGeoIdx];

			while(!feof(fp))
			{
				PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );

				if('}' == sLine[0])
					break;

				if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_NODE_NAME]._tszAseKeyword ) )
				{
					char	sName[64];
					
					PUT_GetStrInQuot(sName, sLine);

					PUT_Strcpy(pCurGeom->GetNodeName(), sName);

				}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_NODE_NAME]._tszAseKeyword ) )
				//----------------------------------------------------------------------------------------
				if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_NODE_TM]._tszAseKeyword ) )
				{
					while( !feof(fp) )
					{
						PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );

						if('}' == sLine[0])
							break;

					}//	while( !feof(fp) )

				}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_NODE_TM]._tszAseKeyword ) )
				//----------------------------------------------------------------------------------------
				if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH]._tszAseKeyword ) )
				{
					while(!feof(fp))
					{
						PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );

						if('}' == sLine[0])
							break;

						if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_NUMVERTEX]._tszAseKeyword ) )
						{
							INT		iNVx;
							sscanf(sLine, "%*s %d", &iNVx);

							pCurGeom->SetTotVtxCnt(iNVx);
							pCurGeom->m_pVtxXyzArr	= new sPRVtx_Xyz[iNVx];
						
						}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_NUMVERTEX]._tszAseKeyword ) )
						//----------------------------------------------------------------------------------------
						if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_NUMFACES]._tszAseKeyword ) )
						{
							INT		iNIx;
							sscanf(sLine, "%*s %d", &iNIx);

							pCurGeom->SetTotIdxCnt(iNIx);
							pCurGeom->m_pIDxArr = new sPRINDEX16[iNIx];
						
						}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_NUMFACES]._tszAseKeyword ) )
						//----------------------------------------------------------------------------------------
						if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_VERTEX_LIST]._tszAseKeyword ) )
						{
							while(!feof(fp))
							{
								PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );

								if('}' == sLine[0])
									break;

								if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_VERTEX]._tszAseKeyword ) )
								{
									INT		nIdx=0;
									FLOAT	x=0.F, y=0.F, z=0.F;
									sscanf(sLine, "%*s %d %f %f %f", &nIdx, &x, &y, &z);

									pCurGeom->m_pVtxXyzArr[nIdx]._fX		= x;
									pCurGeom->m_pVtxXyzArr[nIdx]._fY		= z;
									pCurGeom->m_pVtxXyzArr[nIdx]._fZ		= y;

									//----------------------------------------------------------------------------------------
								}//	eASEKEY_MESH_VERTEX
								//----------------------------------------------------------------------------------------

							}//	while(!feof(fp))

						}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_VERTEX_LIST]._tszAseKeyword ) )
						//----------------------------------------------------------------------------------------
						if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_FACE_LIST]._tszAseKeyword ) )
						{
							while(!feof(fp))
							{
								PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );
								if('}' == sLine[0])
									break;

								if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_FACE]._tszAseKeyword ) )
								{
									INT		nIdx=0;
									INT		a=0, b=0, c=0;
									char	sTmp1[16];									
									sscanf(sLine, "%*s         %d:   %s    %d  %s    %d  %s   %d"
										, &nIdx
										, sTmp1, &a
										, sTmp1, &b
										, sTmp1, &c);

									pCurGeom->m_pIDxArr[nIdx]._wA = a;
									pCurGeom->m_pIDxArr[nIdx]._wB = c;
									pCurGeom->m_pIDxArr[nIdx]._wC = b;

								}//	if(0 == strncmp(sLine, g_ASEKey[8]._tszAseKeyword, g_ASEKey[8].iKey) )
								//----------------------------------------------------------------------------------------
							}// while(!feof(fp))

						}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_FACE_LIST]._tszAseKeyword ) )
						//----------------------------------------------------------------------------------------
						if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_NUMTVERTEX]._tszAseKeyword ) )
						{
							int	nTotTvtx = 0;
							sscanf( sLine, "%*s %d", &nTotTvtx );
							pCurGeom->SetTotTVtxCnt( nTotTvtx );
							pCurGeom->m_pTVtxArr	=	new sPRTVtx[nTotTvtx];						

						}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_NUMTVERTEX]._tszAseKeyword ) )
						//----------------------------------------------------------------------------------------


						if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_TVERTLIST]._tszAseKeyword ) )
						{
							while( !feof(fp) )
							{
								PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );
								if('}' == sLine[0])
									break;

								if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_TVERT]._tszAseKeyword ) )
								{
									INT		nIdx=0;
									FLOAT	u=0.F, v=0.F, w=0.F;
									sscanf(sLine, "%*s %d %f %f %f", &nIdx, &u, &v, &w);

									pCurGeom->m_pTVtxArr[nIdx]._fU = u;
									pCurGeom->m_pTVtxArr[nIdx]._fV = 1.0f-v;
									pCurGeom->m_pTVtxArr[nIdx]._fW = w;						

								}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_TVERT]._tszAseKeyword ) )
								//----------------------------------------------------------------------------------------
							}//	while( !feof(fp) )
							
						}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_TVERTLIST]._tszAseKeyword ) )
						//----------------------------------------------------------------------------------------
						if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_NUMTVFACES]._tszAseKeyword ) )
						{
							int nTotTIdx = 0;
							sscanf(sLine, "%*s %d", &nTotTIdx);
							pCurGeom->SetTotTidxCnt( nTotTIdx );
							pCurGeom->m_pTIDxArr = new sPRINDEX16[nTotTIdx];

						}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_NUMTVFACES]._tszAseKeyword ) )
						//----------------------------------------------------------------------------------------
						if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_TFACELIST]._tszAseKeyword ) )
						{
							while( !feof(fp) )
							{
								PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );
								if('}' == sLine[0])
									break;

								if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_TFACE]._tszAseKeyword ) )
								{
									int	nIdx = 0;
									int a = 0, b = 0, c = 0;

									sscanf(sLine, "%*s %d %d %d %d", &nIdx, &a, &b, &c);

									pCurGeom->m_pTIDxArr[nIdx]._wA = a;
									pCurGeom->m_pTIDxArr[nIdx]._wB = c;
									pCurGeom->m_pTIDxArr[nIdx]._wC = b;

								}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_TFACE]._tszAseKeyword ) )
								//----------------------------------------------------------------------------------------

							}//	while( !feof(fp) )

						}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_TFACELIST]._tszAseKeyword ) )
						//----------------------------------------------------------------------------------------
						if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_NORMALS]._tszAseKeyword ) )
						{
							pCurGeom->m_pVtxNormArr = new sPRVtx_Xyz[ pCurGeom->GetTotVtxCnt() ];

							while( !feof(fp) )
							{
								PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );
								if('}' == sLine[0])
									break;

							}//	while( !feof(fp) )

						}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH_NORMALS]._tszAseKeyword ) )
						//----------------------------------------------------------------------------------------

					}// while(!feof(fp))

				}// if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MESH]._tszAseKeyword ) )
				//----------------------------------------------------------------------------------------


				if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_TM_ANIMATION]._tszAseKeyword ) )
				{
					while( !feof(fp) )
					{
						PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );
						if('}' == sLine[0])
							break;

						if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_CONTROL_ROT_TRACK]._tszAseKeyword ) )
						{
							PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );
							if('}' == sLine[0])
								break;

						}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_CONTROL_ROT_TRACK]._tszAseKeyword ) )
						//----------------------------------------------------------------------------------------
						if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_CONTROL_POS_TRACK]._tszAseKeyword ) )
						{
							PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );
							if('}' == sLine[0])
								break;

						}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_CONTROL_POS_TRACK]._tszAseKeyword ) )
						//----------------------------------------------------------------------------------------
						if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_CONTROL_SCALE_TRACK]._tszAseKeyword ) )
						{
							PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );
							if('}' == sLine[0])
								break;

						}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_CONTROL_SCALE_TRACK]._tszAseKeyword ) )
						//----------------------------------------------------------------------------------------
						if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_CONTROL_ROT_TCB]._tszAseKeyword ) )
						{
							PUT_GetStrOneLineInFile( sLine, MAX_PARSE_LINE, fp );
							if('}' == sLine[0])
								break;

						}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_CONTROL_ROT_TCB]._tszAseKeyword ) )
						//----------------------------------------------------------------------------------------

					}//	while( !feof(fp) )

				}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_TM_ANIMATION]._tszAseKeyword ) )


				if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MATERIAL_REF]._tszAseKeyword ) )
				{
					int nMtrlRef = 0;
					sscanf(sLine, "%*s %d", &nMtrlRef);
					pCurGeom->SetMtrlRef( nMtrlRef );

				}//	if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_MATERIAL_REF]._tszAseKeyword ) )

			}// while(!feof(fp))

		}// if( PUT_StrNiCmp( sLine, g_ASEKey[eASEKEY_GEOMOBJECT]._tszAseKeyword ) )

	}// while(!feof(fp))

	fclose(fp);

	int nCurGeo = 0;
	int nCurTIdx = 0;

	PUT_FOR( nCurGeo, 0, m_nTotGeom )
	{
		CPRAseGeom* pCurGeom = &m_pGeomArr[nCurGeo];
		int			nTotTIdx = pCurGeom->GetTotTIdxCnt();
		int			nMtrlRef = pCurGeom->GetMtrlRef();

		if( pCurGeom->m_pVtxXyzArr )
		{
			pCurGeom->SetFVF( sPRVtx_Xyz::FVF );
			pCurGeom->AddFVF( D3DFVF_DIFFUSE );
		}

		if( pCurGeom->m_pVtxNormArr )	
			pCurGeom->AddFVF( D3DFVF_NORMAL );	

		if( 0 < nTotTIdx && 0 <= nMtrlRef )
		{
			pCurGeom->AddFVF( D3DFVF_TEX1 );

			PUT_FOR( nCurTIdx, 0, nTotTIdx )
			{
				int nTa = pCurGeom->m_pTIDxArr[nCurTIdx]._wA;
				int nTb = pCurGeom->m_pTIDxArr[nCurTIdx]._wB;
				int nTc = pCurGeom->m_pTIDxArr[nCurTIdx]._wC;

				int nVa = pCurGeom->m_pIDxArr[nCurTIdx]._wA;
				int nVb = pCurGeom->m_pIDxArr[nCurTIdx]._wB;
				int nVc = pCurGeom->m_pIDxArr[nCurTIdx]._wC;

				pCurGeom->m_pTVtxArr[nTa]._nVtxIdx = nVa;
				pCurGeom->m_pTVtxArr[nTb]._nVtxIdx = nVb;
				pCurGeom->m_pTVtxArr[nTc]._nVtxIdx = nVc;

			}//	PUT_FOR( nCurTIdx, 0, nTotTIdx )

		}//	if( 0 < nTotTIdx && 0 <= nMtrlRef )

	}//	PUT_FOR( nCurGeo, 0, m_nTotGeom )

 
	return true;

}//	Load
//----------------------------------------------------------------------------------------
bool	CPRMdlAse::OnCreate( void* pDev, void* ptszFName, void* ptszMdlTxtrPath )
{
	m_pDev	= (LPDIRECT3DDEVICE9)pDev;
	PUT_Strcpy( m_tszFile, (TCHAR*)ptszFName );

	if( !Load() )
		return false;

	Confirm( m_tszFile );

	if( !CreateVtx( m_pDev ) )
		return false;

	if( !CreateIdx( m_pDev ) )
		return false;

	if( !CreateTexture( m_pDev, (TCHAR*)ptszMdlTxtrPath ) )
		return false;

	return true;

}//	OnCreate
//----------------------------------------------------------------------------------------
bool	CPRMdlAse::OnUpdate( float fElapsedTime )
{
	return true;

}//	OnUpdate
//----------------------------------------------------------------------------------------
HRESULT CPRMdlAse::OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime )
{
	devSetRSZEnable( pDev, TRUE );
	devSetRSCullMode( pDev, D3DCULL_CCW );
//	devSetRSFillMode( pDev, D3DFILL_WIREFRAME );
//	devSetTxtr( pDev, 0, NULL );
	
	for( int nCur = 0; nCur < m_nTotGeom; ++nCur )
	{
		CPRAseGeom* pCurGeom = &m_pGeomArr[nCur];

		
		DWORD dwFVF = pCurGeom->GetFVF();
		devSetFVF( pDev, dwFVF );
		if( pCurGeom->GetFVF() && D3DFVF_NORMAL )
			devSetRSLightEnable( pDev, TRUE );
		else
			devSetRSLightEnable( pDev, FALSE );


		devSetRSLightEnable( pDev, FALSE );
		
		PRDXTXTRBUFF9 pTmpTxtr = NULL;
		if( 0 <= pCurGeom->GetMtrlRef() )		
			pTmpTxtr = m_pMtrlArr[pCurGeom->GetMtrlRef()]._pD3dTxtr;

		devSetTxtr( pDev, 0, pTmpTxtr );

//		if( !PUT_StrNiCmp( pCurGeom->GetNodeName(), PUT_CSTR_TCHAR("Bip") ) )
			pCurGeom->OnRender( pDev, fElapsedTime );
	}

//	devSetRSFillMode( pDev, D3DFILL_SOLID );
//	devSetRSCullMode( pDev, D3DCULL_CCW );
//	devSetRSLightEnable( pDev, TRUE );

	return S_OK;

}//	OnRender
//----------------------------------------------------------------------------------------
//	EOF