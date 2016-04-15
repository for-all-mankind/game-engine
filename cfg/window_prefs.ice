Resolution: struct
  width : u32;
  height: u32;
end

WindowMode: stuct
  window_title: string;
  resolution  : Resolution;
  full_screen : boolean;
end

window_mode := WindowMode{ "Ice Engine", Resolution{ 800u, 600u }, false };