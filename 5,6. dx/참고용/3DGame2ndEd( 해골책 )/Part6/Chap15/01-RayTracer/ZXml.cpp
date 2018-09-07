#include <stdio.h>
#include "zxml.h"

ZXML::ZXML()
{
	m_pXMLDoc = NULL;
	CoInitialize(NULL);
	CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_ALL, IID_IXMLDOMDocument, (void**)&m_pXMLDoc);
}

ZXML::ZXML( LPCTSTR url )
{
}

ZXML::~ZXML()
{
	CoUninitialize();
}

int ZXML::Open( LPCTSTR url )
{
	HRESULT	hr;
	BOOL bRet = TRUE;

	FILE* fp;
	fp = fopen( url, "rt" );
	if( !fp ) return FALSE;
	fclose( fp );

	short sResult = FALSE;

	m_pXMLDoc->put_async(FALSE);

	_bstr_t varString = (LPCTSTR)url;
	VARIANT path;
	path.vt = VT_BSTR;
	path.bstrVal = varString;

	hr = m_pXMLDoc->load(path, &sResult);
	if(FAILED(hr)) return FALSE;

	return bRet;
}

int ZXML::Close()
{
	m_pXMLDoc->Release();

	return 1;
}

IXMLDOMNodeList* ZXML::FindElement( LPCTSTR strElement )
{
	IXMLDOMNodeList* pNodeList = NULL;
	
	if(m_pXMLDoc == NULL)
		return pNodeList;

	_bstr_t bstrPath = strElement;
	m_pXMLDoc->selectNodes(bstrPath, &pNodeList);

	return pNodeList;
}

IXMLDOMNodeList* ZXML::FindElement( IXMLDOMNode* pNode, LPCTSTR strElement )
{
	IXMLDOMNodeList* pNodeList = NULL;
	
	if(pNode == NULL)
		return pNodeList;

	_bstr_t bstrPath = strElement;
	pNode->selectNodes(bstrPath, &pNodeList);

	return pNodeList;
}

int	ZXML::GetElementText( IXMLDOMNode* pNode, LPSTR strRet )
{
	BSTR			bstr = NULL;
	
	pNode->get_text( &bstr );
	strcpy( strRet,(const char*)_bstr_t(bstr,FALSE) );
//	wcstombs( strRet, bstr, 128 );
//	::SysFreeString( bstr );

	return 1;
}

int ZXML::GetAttributeText( IXMLDOMNode* pNode, LPSTR strAttrName, LPSTR strRet )
{
	wchar_t					wstrAttr[128];
	IXMLDOMNode*			pAttrNode = NULL;
	IXMLDOMNamedNodeMap*	pMap = NULL;
	VARIANT					varValue;

	int n = (int)mbstowcs( wstrAttr, strAttrName, 128 );
	pNode->get_attributes( &pMap );
	pMap->getNamedItem( wstrAttr, &pAttrNode );
	pAttrNode->get_nodeValue( &varValue );
	strcpy( strRet,(const char*)_bstr_t(varValue.bstrVal,FALSE) );
//	wcstombs( strRet, varValue.bstrVal , 128 );

	S_REL( pAttrNode );
	S_REL( pMap );

	return 1;
}
