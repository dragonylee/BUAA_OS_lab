in=$1
out=$2

sed -n '8,1p' $in > $out
sed -n '32,1p' $in >> $out
sed -n '128,1p' $in >> $out
sed -n '512,1p' $in >> $out
sed -n '1024,1p' $in >> $out
