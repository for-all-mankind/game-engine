WindowMode: object
  title       :: "Ice Engine";
  full_screen :: false;
  width       :: 800;
  height      :: 600;
end


foo: int = 10;

scope
  bar: borrow ^int = &foo;

  *bar = 20;
end
