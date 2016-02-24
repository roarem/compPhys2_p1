class Foo {
  private:
    int    a;
    double b;
    std::vector<double> ds;

  Foo(const Foo & foo)  // copy-constructor 
  : a { foo.a  },
    b { foo.b  },
    ds{ foo.ds } { 
  };
  //Foo(Foo && foo);  // move-constructor

  void resetTo(const Foo & foo) {
    this->a  = foo.a;
    this->b  = foo.b;
    this->ds = foo.ds;
  };
};

void main() {
  std::vector<Foo> v;
  for ( int i = 0; i < 10; ++i ) {
    v.
  }
}
