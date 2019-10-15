filename = '/home/mikhail/Yama.txt';
delimiter = ' ';
formatSpec = '%f%f%[^\n\r]';

fileID = fopen(filename,'r');

dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'TextType', 'string',  'ReturnOnError', false);
Yama = table(dataArray{1:end-1}, 'VariableNames', {'x','y'});

plot(Yama.x, Yama.y, 'r');
hold on;

fclose(fileID);
clearvars filename delimiter formatSpec fileID dataArray ans;

x = [0, 25, 50, 75, 100, 150, 170, 200, 250, 280, 225, 10, 270];
n=length(x);

xs = 125.777;
ys = gety(1, xs, Yama.x, Yama.y)

y = gety(n, x, Yama.x, Yama.y);

disp(x)
disp(y)

%lagr
yl=lagr(n, Yama.x, x, y);
plot(Yama.x , yl, 'b')
hold on;
%nt
yn=newt(n, Yama.x, x, y);
plot(Yama.x , yn, 'g--')
hold on;

disp(xs);
disp(ys);
ynr=gety(1, xs, Yama.x, yn);
ylr=gety(1, xs, Yama.x, yl);
disp(ylr);
disp(ynr);

legend('Яма','Полином Лагранжа', 'Полином Ньютона', 'Location', 'southoutside', 'Orientation', 'horizontal');
xlabel('x, мм');
ylabel('y, мм');
title('Яма');
axis([0 280 0 200]);
grid on;