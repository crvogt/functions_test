spaceVal = 10;
holdx = [-spaceVal -spaceVal spaceVal spaceVal];
holdy = [-spaceVal spaceVal -spaceVal spaceVal];

x = [0.1 0.25 0.25 0.25 0.4];
y = [0.5 0.5 0 1 0.5];

figure(1)

for it=-5:1:5
	it
	hold on
	plot(holdx, holdy, '*')
	xN = x .* it;
	yN = y .* it;
	plot(xN(1), yN(1), '*', 'markersize', 2)
	plot(xN(2), yN(2), '*', 'markersize', 3)
	plot(xN(3), yN(3), '*', 'markersize', 4)
	plot(xN(4), yN(4), '*', 'markersize', 5)
	plot(xN(5), yN(5), '*', 'markersize', 6)
	hold off
	pause(1)
	clf
end

boxX = [0 0 1 1 0];
boxY = [0 1 1 0 0];

figure(2)

for jt=-5:1:5
	jt
	hold on
	plot(holdx, holdy, '*')
	boxX2 = boxX + x(1) * jt;
	boxY2 = boxY + y(1) * jt;
	boxX3 = boxX + x(2) * jt;
	boxY3 = boxY + y(2) * jt;
	boxX4 = boxX + x(3) * jt;
	boxY4 = boxY + y(3) * jt;
	boxX5 = boxX + x(4) * jt;
	boxY5 = boxY + y(4) * jt;
	boxX6 = boxX + x(5) * jt;
	boxY6 = boxY + y(5) * jt;
	plot(boxX2, boxY2, 'r')
	plot(boxX3, boxY3)
	plot(boxX4, boxY4)
	plot(boxX5, boxY5)
	plot(boxX6, boxY6)
	hold off
	pause(1)
	clf
end