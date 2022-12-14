% Aproximacia zavislosti nadmorskej vysky od atmosferickeho tlaku 
% polynomom 3. radu. 
% Zdroj dat: https://www.mide.com/air-pressure-at-altitude-calculator

meters = [-1524 -1219 -914 -610 -305 -152 0 152 305 457 610 762 914 ...
    1067 1219 1372 1524 1829 2134 2438 2743 3048 4572 6096 7620 ...
    9144 10668 12192 13716 15240 16764 18288 19812];

hPa = [121.0 116.9 112.8 108.9 105.0 103.2 101.3 99.5 97.7 96.0 94.2 ...
    92.5 90.8 89.1 87.5 85.9 84.3 81.2 78.2 75.3 72.4 69.7 57.2 46.6 ...
    37.6 30.1 23.8 18.8 14.7 11.6 9.1 7.2 5.6] * 10;

for x = 1:1:1200
    y(x) = -1.345e-11*x^5 + 5.875e-08*x^4 -0.0001038*x^3 + 0.09745*x^2 ...
    -59.44*x + 2.065e+04;
end


plot(1:1200, y)
