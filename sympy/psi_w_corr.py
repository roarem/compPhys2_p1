import sympy as sym

x,y,z,r,f,u,a,b,boson = sym.symbols('x y z r f u a b boson')
g = sym.functions.exp(-a*(x**2 + y**2 + b*z**2))
f = 1 - boson/(sym.sqrt(r))
u = sym.log(f)

def nabla2():
    g_mark = sym.Derivative(g,x).doit() + sym.Derivative(g,y).doit() + sym.Derivative(g,z).doit()
    g_2mark = sym.Derivative(g_mark,x).doit() + sym.Derivative(g_mark,y).doit() + sym.Derivative(g_mark,z).doit()
    print(g_2mark.simplify())

def uder():
    u_mark = sym.Derivative(u,r).doit() 

    u_2mark = sym.Derivative(u_mark,r).doit()

    print(u_mark.simplify())
    print(u_2mark.simplify())

nabla2()
