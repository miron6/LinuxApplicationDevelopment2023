set pagination off
set $iter = 1
break 27 if $iter >=28 & $iter++ <= 35
    command 1
    printf "@@@%d %d %d %d\n", start, end, step, i
    continue
end
run -100 100 3 > /dev/null
quit
