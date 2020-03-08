file=$1
s=$2
t=$3

sed -i "s/$s/$t/g" $file
