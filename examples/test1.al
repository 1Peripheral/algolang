x = 1
while x repeat
  read x 
  if x == -1 then
    write "breaking out"
    break
  end
  if x == 1 then
    write "continuing"
    continue
  end
  write "normal loop"
end

write "GOOD BYE"
