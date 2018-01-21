%{

#include <iostream>
#include <stack>
#include <cstring>

std::stack<std::string> stk;
%}
letter      [a-zA-Z]
blank       [ ]


%%
{blank}      { stk.push(" ");              }
a            { stk.push(u8"\u0250");       }
b            { stk.push(u8"\u0071");       }
c            { stk.push(u8"\u0254");       }
d            { stk.push(u8"\u0070");       }
e            { stk.push(u8"\u01DD");       }
f            { stk.push(u8"\u025F");       }
g            { stk.push(u8"\u0253");       }
h            { stk.push(u8"\u0265");       }
i            { stk.push(u8"\u0131");       }
j            { stk.push(u8"\u027E");       }
k            { stk.push(u8"\u029E");       }
l            { stk.push(u8"\u006C");       }
m            { stk.push(u8"\u026F");       }
n            { stk.push(u8"\u0075");       }
o            { stk.push(u8"\u006F");       }
p            { stk.push(u8"\u0064");       }
q            { stk.push(u8"\u0062");       }
r            { stk.push(u8"\u0279");       }
s            { stk.push(u8"\u0073");       }
t            { stk.push(u8"\u0287");       }
u            { stk.push(u8"\u006E");       }
v            { stk.push(u8"\u028C");       }
w            { stk.push(u8"\u028D");       }
x            { stk.push(u8"\u0078");       }
y            { stk.push(u8"\u028E");       }
z            { stk.push(u8"\u007A");       }
A            { stk.push(u8"\u2200");       }
B            { stk.push(u8"\u15FA");       }
C            { stk.push(u8"\u0186");       }
D            { stk.push(u8"\u15E1");       }
E            { stk.push(u8"\u018E");       }
F            { stk.push(u8"\u2132");       }
G            { stk.push(u8"\u2141");       }
H            { stk.push(u8"\u0048");       }
I            { stk.push(u8"\u0049");       }
J            { stk.push(u8"\u017F");       }
K            { stk.push(u8"\u22CA");       }
L            { stk.push(u8"\u2142");       }
M            { stk.push(u8"\u0057");       }
N            { stk.push(u8"\u004E");       }
O            { stk.push(u8"\u004F");       }
P            { stk.push(u8"\u0500");       }
Q            { stk.push(u8"\u038C");       }
R            { stk.push(u8"\u1D1A");       }
S            { stk.push(u8"\u0053");       }
T            { stk.push(u8"\u22A5");       }
U            { stk.push(u8"\u2229");       }
V            { stk.push(u8"\u039B");       }
W            { stk.push(u8"\u004D");       }
X            { stk.push(u8"\u0058");       }
Y            { stk.push(u8"\u2144");       }
Z            { stk.push(u8"\u005A");       }
1            { stk.push(u8"\u21C2");       }
2            { stk.push(u8"\u1614");       }
3            { stk.push(u8"\u0190");       }
4            { stk.push(u8"\u07C8");       }
5            { stk.push(u8"\u03DA");       }
6            { stk.push(u8"\u0039");       }
7            { stk.push(u8"\u3125");       }
8            { stk.push(u8"\u0038");       }
9            { stk.push(u8"\u0036");       }
0            { stk.push(u8"\u0030");       }
";"          { stk.push(u8"\u061B");       }
","          { stk.push(u8"\u0027");       }
"."          { stk.push(u8"\u02D9");       }
"'"          { stk.push(u8"\u002C");       }
"\""         { stk.push(u8"\u201E");       }
"!"          { stk.push(u8"\u00A1");       }
"?"          { stk.push(u8"\u00BF");       }
"_"          { stk.push(u8"\u203E");       }
"&"          { stk.push(u8"\u214B");       }
"\n"         { while( !stk.empty() ) {
                    std::cout << stk.top();
                    stk.pop();
               }
               std::cout << std::endl;
             }
.            { }
%%



int yywrap() {
    yylex_destroy();
    return 1;
}

