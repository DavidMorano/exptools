
#ifndef _PATH_H
#define _PATH_H 1
//#pragma once

#include <String.h>
#include <List.h>
#include <sys/file.h>

class Path;
class List(Path);
class Search_path;

class Path {
public:

// enums
	enum binary_test_flag { 
		ef = 0, nt = 1, ot = 2 
	};
	enum unary_test_flag {  
		a = 'a',  // undocumented in ksh book; 
			  // means "file can be statted"
		r = 'r', w = 'w', x = 'x', f = 'f', 
		d = 'd', c = 'c', b = 'b', p = 'p', 
		u = 'u', g = 'g', k = 'k', s = 's', 
		L = 'L', O = 'O', G = 'G', S = 'S' 
	};
	enum id_type { 
		effective_id = 0, real_id = 1 
	};
	enum completion { 
		no_completion = 0, 
		unique_completion = 1, 
		several_completions = 2 
	};
	enum slash_style {
		gnulike_slashes, unixlike_slashes
	};
	enum access_mode { 
		r_ok = R_OK, w_ok = W_OK, x_ok = X_OK, f_ok = F_OK 
	};

// constructors
	Path();
	Path(const char *);
	Path(const char * dirpath, const char * base, const char * ext = 0);	// Final '/' on <dirpath> is optional.
	Path(const List(Path) &);
	Path(const String &);
	Path(const Path &);

// components
	Path dirname() const;
	String basename(const char * suffix = 0) const;
	void explode(List(Path) &) const;

// path catenation
	Path & operator/=(const Path &);

// relative and absolute versions of path names
	int is_relative() const;
	int is_absolute() const;
	Path absolute() const;
	Path relative() const;
	Path relative(Path wrt) const;

// wildcard expansion
	void expand_wildcards(List(Path) &) const;

// ksh file name completion
	completion complete(String &) const;

// searching in path
	int find_in_search_path(Path &, unary_test_flag = x, id_type = effective_id) const;
	int find_in_search_path(Path &, const Search_path &, unary_test_flag = x, id_type = effective_id) const;
	int find_all_in_search_path(List(Path) &, unary_test_flag = x, id_type = effective_id) const;
	int find_all_in_search_path(List(Path) &, const Search_path &, unary_test_flag = x, id_type = effective_id) const;

// test(1)
	int test(unary_test_flag = a, id_type = effective_id) const;
	int test(binary_test_flag, const Path &, id_type = effective_id) const;

// assignment
	Path & operator=(const Path &);

// slash style
	static slash_style get_slash_style();
	static void set_slash_style(slash_style);

// length restrictions
	static int get_max_file_length();
	static void set_max_file_length(int);
	static int get_max_path_length();
	static void set_max_path_length(int);

// conversions
	operator const char * () const;
	operator String() const;

// objections
	static Objection filename_too_long;
		// default:  ignore
		// recovery: truncate offending file or directory name
	static Objection path_too_long;
		// default:  ignore
		// recovery: ignore
	static Objection no_wd;
		// default:  abort with error message
		// recovery: set working directory to "/"

// miscellaneous
	int is_wd() const;
	int length() const;

private:
	String rep;
	static int max_path_length;
	static int max_file_length;
	static void empty_list(List(Path)&);
	static slash_style slsh_style;
	void canonicalize();
	void build_from(const char *, const char *, const char *);
};		

//global functions
Path operator/(const Path & s, const Path & t);
int operator==(const Path &, const Path &);
int operator!=(const Path &, const Path &);
ostream & operator<<(ostream &, const Path &);
istream & operator>>(istream &, Path &);


Listdeclare(Path)

class Search_path : public List(Path) {
public:

//constructors
	Search_path();	// empty search path
	Search_path(const char * colon_separated_list_of_directories);
	Search_path(const Search_path &);
	Search_path & operator=(const Search_path &);

// conversions
	operator const char * () const;
	operator String() const;
};

ostream & operator<<(ostream &, const Search_path &);
istream & operator>>(istream &, Search_path &);


#endif /* _PATH_H */

