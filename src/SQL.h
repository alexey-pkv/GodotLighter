#ifndef GODOTLIGHTER_H
#define GODOTLIGHTER_H


namespace sqlighter
{
	class SQLighter;
}


namespace godotlighter
{
	class SQL
	{
	public:
		static const char* sqlite_version();
		static const char* sqlighter_version();
		static const char* library_version();
	};
}


#endif