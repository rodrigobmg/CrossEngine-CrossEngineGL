/****************************************************************************
Copyright (c) 2015 LiangYue.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sub license, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#pragma once


#include "CrossEngine.h"


namespace CrossEngine {

	class _CrossExport CSound : public CResource
	{
		friend class CSoundPtr;
		friend class CSoundManager;


		// ����/��������
	protected:
		CSound(CResourceManager *pResourceManager);
		virtual ~CSound(VOID);


		// ����
	public:
		virtual VOID Init(VOID);                                                                   // ��ʼ����Դ
		virtual VOID Free(VOID);                                                                   // �ͷ���Դ

	public:
		virtual TYPE GetType(VOID) const;                                                          // �������
		virtual BOOL IsValid(VOID) const;                                                          // ��Ч�Լ��

	public:
		virtual BOOL CopyFrom(const CResource *pCopyFrom);                                         // ������Դ

		virtual BOOL LoadFromFile(const CHAR *szFileName);                                         // ���ļ�������Դ
		virtual BOOL LoadFromZip(const CHAR *szZipName, const CHAR *szFileName);                   // ��ѹ����������Դ
		virtual BOOL LoadFromZip(ZZIP_DIR *pZipPack, const CHAR *szFileName);                      // ��ѹ����������Դ
		virtual BOOL LoadFromStream(CStream *pStream);                                             // ��������������Դ

	public:
		FMOD_SOUND* GetSound(VOID) const;                                                          // �������


		// ����
	protected:
		FMOD_SOUND *m_pFModSound;                                                                  // FMOD����ָ��
	};

	class _CrossExport CSoundPtr : public CSharedPtr<CSound>
	{
		// ����/��������
	public:
		CSoundPtr(VOID) : CSharedPtr<CSound>() {}
		CSoundPtr(const CSound *pSound) : CSharedPtr<CSound>(pSound) {}
		CSoundPtr(const CSoundPtr &ptrSound) : CSharedPtr<CSound>(ptrSound) {}
		CSoundPtr(const CResourcePtr &ptrResource) { Set(static_cast<CSound*>(ptrResource.GetPointer()), ptrResource.GetRefCount()); }
		virtual ~CSoundPtr(VOID) {}


		// ����
	protected:
		virtual VOID FreePointer(VOID)
		{
			if (m_pPointer) {
				m_pPointer->GetResourceManager()->DestroyResource(m_pPointer);
			}
		}

	public:
		CSoundPtr& operator = (const CResourcePtr &ptrResource)
		{
			Set(static_cast<CSound*>(ptrResource.GetPointer()), ptrResource.GetRefCount());
			return *this;
		}

		operator CResource* ()
		{
			return (CResource *)m_pPointer;
		}

		operator const CResource* () const
		{
			return (const CResource *)m_pPointer;
		}
	};
}