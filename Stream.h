#pragma once

/*---------------------------------------------------------------------*/
/*���Ž� : ���Ź����� ������-> ����ȭ��Ʈ��-> ��Ŷ���κ�ȯ -> ���� ����.
/*�۽Ž� : ��Ʈ���� ���� ä��� -> �۽Ź��۷� ����.
/*���� !!! : �ټ��� ����� �����带 ���� �ݵ�� RC����Ұ� .���� �۽� �Ϸ� ����Ʈ ���ڸ� Ȯ���ؼ�*/
/*��Ʈ����ü�� ī������ ���ҽ�Ű�� �װͿ� ���� �ٽ� �޸�Ǯ�� �־���Ѵ�. */
/*---------------------------------------------------------------------*/


namespace SSE
{

	class CSSEStream
	{
	public:

		int m_nOffsetOut = 0;
		vector<char> m_buffer;
		CRITICAL_SECTION m_CS;
		int m_nRefCnt = 0;


	public:

		void Append(const void * data, int size);
		void Clear();
		size_t GetSize() { return m_buffer.size(); }
		char* GetData() { return &(m_buffer[0]); }

		int  GetRefCnt() { return m_nRefCnt; }
		void AddRefCnt() { ++m_nRefCnt; }
		void SubRefCnt()
		{
			LOCKNOW(&m_CS)
			{
				m_nRefCnt--;
			}
		}

		void Ready_SendOrder(SendOrder& S);

		CSSEStream& operator <<(int Data);
		CSSEStream& operator <<(short& Data);
		CSSEStream& operator <<(unsigned int& Data);

		CSSEStream& operator <<(const wstring& Data);
		CSSEStream& operator <<(float& Data);
		template <typename T>
		CSSEStream& operator <<(const vector<T>& Data)
		{
			unsigned int S = Data.size();
			*this << S;

			if (S == 0)
				return *this;

			char* p = (char*)Data.data();
			Append(p, sizeof(T) * S);

			return *this;
		}

		CSSEStream& operator >>(int& Data);
		CSSEStream& operator >>(short& Data);
		CSSEStream& operator >>(unsigned int& Data);


		CSSEStream& operator >>(wstring& Data);
		CSSEStream& operator >>(float& Data);

		template <typename T>
		CSSEStream& operator >>(vector<T>& Data)
		{
			unsigned int S;
			*this >> S;
			for (unsigned int i = 0; i < S; ++i)
			{
				Data.push_back(*((T*)(&m_buffer[m_nOffsetOut])));
				m_nOffsetOut += sizeof(T);
			}

			return *this;
		}



		CSSEStream()
		{
			InitializeCriticalSection(&m_CS);
		}
		virtual ~CSSEStream()
		{
			LOCKNOW(&m_CS)
			{

			}

			DeleteCriticalSection(&m_CS);
		}
	};


}




