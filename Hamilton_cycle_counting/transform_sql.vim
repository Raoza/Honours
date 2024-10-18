execute "normal gg"
g/^INSERT INTO testgraphs/norm 0D
g/^INSERT INTO testgraphs/d
%s/);/,/g
g/,$/s/,$/;/
wq output.txt

