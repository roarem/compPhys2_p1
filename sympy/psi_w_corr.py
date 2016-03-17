import sympy as sym
from sympy.vector import CoordSysCartesian

x,y,z,r,f,u,a,b,boson = sym.symbols('x y z r f u a b boson')
C = CoordSysCartesian('C')
r = x*C.i + y*C.j + z*C.k
g = sym.functions.exp(-a*(x**2 + y**2 + b*z**2))
f = 1 - boson/(sym.sqrt(x**2+y**2+z**2))
u = sym.log(f)

def nabla2():
    g_mark = sym.Derivative(g,x).doit() + sym.Derivative(g,y).doit() + sym.Derivative(g,z).doit()
    g_2mark = sym.Derivative(g_mark,x).doit() + sym.Derivative(g_mark,y).doit() + sym.Derivative(g_mark,z).doit()
    print(g_2mark.simplify())

def uder():
    u_mark = sym.Derivative(u,x).doit() +\
            sym.Derivative(u,y).doit() +\
            sym.Derivative(u,z).doit()

    u_2mark = sym.Derivative(u_mark,x).doit() +\
            sym.Derivative(u_mark,y).doit() +\
            sym.Derivative(u_mark,z).doit()

    print(u_mark.simplify())
    #print(u_2mark.simplify())

uder()
