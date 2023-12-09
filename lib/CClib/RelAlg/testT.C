#include <relation.h>

int_domain(Id);
string_domain(Uname,9);
string_domain(Pathname,20); // shortened for convenience in printing
string_domain(Password,14);
string_domain(Comment,10);
attribute(user,Uname);
attribute(group,Uname);
attribute(user_password,Password);
attribute(group_password,Password);
attribute(uid,Id);
attribute(gid,Id);
attribute(gcos,Comment);
attribute(members,Comment);
attribute(home,Pathname);
attribute(shell,Pathname);
#define passwd_attrs user%user_password/uid/gid/gcos/home/shell
#define group_attrs group%group_password/gid/members
AF_Relation etcpasswd(passwd_attrs,"/etc/passwd",':',READONLY);
AF_Relation etcgroup(group_attrs,"/etc/group",':',READONLY);

main()
{
cout << "\et\et\etUSER INFORMATION:\en"
     <<  (etcpasswd & etcgroup)[user/group/home/shell] ;
return 0;
}
