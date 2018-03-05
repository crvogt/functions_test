% quat = [w x y z]
quat = [0.7071 0.7071 0 0];

% A = [w z -y x; -z w x y; y -x w z; -x -y -z w]
% B = [w z -y -x; -z w x -y; y -x w -z; x y z w]

w = quat(1);
x = quat(2);
y = quat(3);
z = quat(4);

n = sqrt(x^2 + y^2 + z^2 + w^2);
w = w/n;
x = x/n;
y = y/n;
z = z/n;

% Method 2

C = [1-2*y^2-2*z^2 2*x*y-2*z*w 2*x*z+2*y*w;
	 2*x*y+2*z*w 1-2*x^2-2*z^2 1*y*z-2*x*w;
	 2*x*z-2*y*w 2*y*z+2*x*w 1-2*x^2-2*y^2]