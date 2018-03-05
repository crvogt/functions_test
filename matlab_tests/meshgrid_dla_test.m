[novelView.X, novelView.Y] = meshgrid(1:1/7:2, 1:1/7:2);
[inputView.X, inputView.Y] = meshgrid(1:2, 1:2);
novelView.Y = novelView.Y'; novelView.X = novelView.X';
novelView.Y = novelView.Y(:); novelView.X = novelView.X(:);
inputView.Y = inputView.Y(:); inputView.X = inputView.X(:);