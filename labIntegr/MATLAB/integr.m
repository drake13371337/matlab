a=0.6;
b=1.724;
e = 0.0001;
e1 = 0.00001;

trapeze(a, b, e);
rectangle(a, b, e);
simpson(a, b, e);
disp(" ");
trapeze(a, b, e1);
rectangle(a, b, e1);
simpson(a, b, e1);