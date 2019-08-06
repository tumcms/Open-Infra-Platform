% function [x, y, X, Y] = clothoid()
% syms R L l
% k = l /(R*L)
% 
% [x, y, X, Y] = approxCuve(k, 4)
% end

% function [x, y, X, Y] = bloss()
% syms R L l
% k = 3 * l^2 /(R*L^2) - 2 * l^3 /(R*L^3)
% [x, y, X, Y] = approxCuve(k, 4)
% end

function [x, y, X, Y] = approxCuve(k, n)
syms L l

O = int(k, l);
x = approxX(O, n);
X = subs(x, l, L);
y = approxY(O, n);
Y = subs(y, l, L);
end

function x = approxX(O, n)
syms l
c = 0;
for i = 0:n-1
   c = c + O^(i*2)/factorial(i*2) * (mod(i,2)*-2 + 1);
end
%c  = 1 - O^2/factorial(2) + O^4/factorial(4) - O^6/factorial(6)
x = int(c, l);
end

function y = approxY(O, n)
syms l
s = 0;
for i = 0:n-1
   s = s + O^(i*2+1)/factorial(i*2+1) * (mod(i,2)*-2 + 1);
end
%s  = O - O^3/factorial(3) + O^5/factorial(5) - O^7/factorial(7)
y = int(s, l);
end