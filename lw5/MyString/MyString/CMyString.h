#pragma once
#include <string>
#include "CMyIterator.h"

class CMyString
{
public:
	using iterator = CMyIterator<char>;
	using const_iterator = CMyIterator<const char>;

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other);
	CMyString(std::string const& stlString);
	~CMyString();
	size_t GetLength()const;
	const char* GetStringData()const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX)const;
	void Clear();

	CMyString const operator=(const char* str2);

	CMyString& operator=(CMyString&& other) noexcept;
	CMyString& operator=(CMyString const& other);

	CMyString& operator+=(const CMyString& str1);
	const char& operator[](size_t index) const;
	char& operator[](size_t index);

	const char& operator[](CMyString::const_iterator it) const;
	char& operator[](CMyString::iterator it);

private:
	char* m_value = nullptr;
	size_t m_length;
};

CMyString const operator+(const CMyString& str1, const CMyString& str2);
CMyString const operator+(const CMyString& str1, const std::string& str2);
CMyString const operator+(const CMyString& str1, const char* str2);

bool const operator==(const CMyString& str1, const CMyString& str2);
bool const operator!=(const CMyString& str1, const CMyString& str2);

bool const operator<(const CMyString& str1, const CMyString& str2);
bool const operator>(const CMyString& str1, const CMyString& str2);

bool const operator>=(const CMyString& str1, const CMyString& str2);
bool const operator<=(const CMyString& str1, const CMyString& str2);