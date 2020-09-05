#include "Stream.h"

namespace SSE
{
	void CSSEStream::Append(const void * Data, int size)
	{
		m_buffer.insert(m_buffer.end(), (char*)Data, (char*)Data + size);

	}

	void CSSEStream::Clear()
	{
		m_nRefCnt = 0;
		m_nOffsetOut = 0;
		m_buffer.clear();
	}

	void CSSEStream::Ready_SendOrder(SendOrder & S)
	{
		S.BUF.len = m_buffer.size();
		S.BUF.buf = GetData();
		S.PStream = this;

	}

	CSSEStream & CSSEStream::operator<<(int Data)
	{
		Append(&Data, sizeof(Data));
		return *this;
		//데이터 입력.

	}

	CSSEStream & CSSEStream::operator>>(int & Data)
	{
		Data = *((int*)(&m_buffer[m_nOffsetOut]));
		m_nOffsetOut += sizeof(Data);
		return *this;
	}

	CSSEStream & CSSEStream::operator>>(short& Data)
	{
		Data = *((short*)(&m_buffer[m_nOffsetOut]));
		m_nOffsetOut += sizeof(Data);
		return *this;
	}

	CSSEStream & CSSEStream::operator>>(unsigned int & Data)
	{
		Data = *((unsigned int*)(&m_buffer[m_nOffsetOut]));
		m_nOffsetOut += sizeof(Data);
		return *this;
	}

	CSSEStream & CSSEStream::operator>>(float & Data)
	{
		Data = *((float*)(&m_buffer[m_nOffsetOut]));
		m_nOffsetOut += sizeof(Data);

		return *this;
	}



	CSSEStream & CSSEStream::operator<<(short & Data)
	{
		Append(&Data, sizeof(Data));
		return *this;
	}

	CSSEStream & CSSEStream::operator<<(unsigned int & Data)
	{
		Append(&Data, sizeof(Data));
		return *this;
	}


	CSSEStream & CSSEStream::operator<<(const wstring & Data)
	{
		*this << (Data.size() * 2);
		Append(Data.data(), Data.size() * 2);
		return *this;
	}

	CSSEStream & CSSEStream::operator<<(float & Data)
	{
		Append(&Data, sizeof(Data));
		return *this;
	}
	CSSEStream & CSSEStream::operator>>(wstring & Data)
	{

		int Size;
		*this >> Size;
		Data.clear();
		Data.append((WCHAR*)(&m_buffer[m_nOffsetOut]), Size / 2);
		m_nOffsetOut += Size;
		return *this;
	}

}

