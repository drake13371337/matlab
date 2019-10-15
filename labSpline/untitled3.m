filename = '/home/mikhail/Yama.txt';
delimiter = ' ';
formatSpec = '%f%f%[^\n\r]';

fileID = fopen(filename,'r');

dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'TextType', 'string',  'ReturnOnError', false);
Yama = table(dataArray{1:end-1}, 'VariableNames', {'x','y'});

plot(Yama.x, Yama.y, 'r');
hold on;

yy = spline(Yama.x, Yama.y, Yama.x);
plot(Yama.x, yy, 'y--');
hold on;

s1=46;
x1 = zeros(1, s1);
k1=1;
for k=1:s1
    x1(k)=Yama.x(k1);
    k1=k1+3;
end
x1(end)=280;
y1=gety(s1, x1, Yama.x, Yama.y);
yy1=spline(x1, y1, Yama.x);
plot(Yama.x, yy1, 'm-.');
hold on;

s2=28;
x2 = zeros(1, s2);
k2=1;
for k=1:s2
    x2(k)=Yama.x(k2);
    k2=k2+5;
end
x2(end)=280;
y2=gety(s2, x2, Yama.x, Yama.y);
yy2=spline(x2, y2, Yama.x);
plot(Yama.x, yy2, 'k:');
hold on;

legend('Яма', 'Сплайн N', 'Сплайн N/3', 'Сплайн N/5', 'Location', 'southoutside', 'Orientation', 'horizontal');
xlabel('x, мм');
ylabel('y, мм');
title('Яма');
axis([0 280 0 200]);
grid on;