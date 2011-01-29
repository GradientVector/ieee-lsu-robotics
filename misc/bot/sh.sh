echo $1 $2
for x in `seq 1 $1`
do
    scrot -d $2 -c
done
