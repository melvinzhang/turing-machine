# from The Annotated Turing, starting from page 115
# print the binary expansion of sqrt(2)
begin ~ P@,R,P1 new

new @ R mark-digits
new * L new

mark-digits 0 R,Px,R mark-digits
mark-digits 1 R,Px,R mark-digits
mark-digits ~ R,Pz,R,R,Pr find-x

find-x x E first-r
find-x @ , find-digits
find-x * L,L find-x

first-r r R,R last-r
first-r * R,R first-r

last-r r R,R last-r
last-r ~ Pr,R,R,Pr find-x

find-digits @ R,R find-1st-digit
find-digits * L,L find-digits

find-1st-digit x L found-1st-digit
find-1st-digit y L found-1st-digit
find-1st-digit z L found-2nd-digit
find-1st-digit ~ R,R find-1st-digit

found-1st-digit 0 R add-zero
found-1st-digit 1 R,R,R find-2nd-digit

find-2nd-digit x L found-2nd-digit
find-2nd-digit y L found-2nd-digit
find-2nd-digit ~ R,R find-2nd-digit

found-2nd-digit 0 R add-zero
found-2nd-digit 1 R add-one
found-2nd-digit ~ R add-one

add-zero r Ps add-finished
add-zero u Pv add-finished
add-zero * R,R add-zero

add-one r Pv add-finished
add-one u Ps,R,R carry
add-one * R,R add-one

carry r Pu add-finished
carry ~ Pu new-digit-is-zero
carry u Pr,R,R carry

add-finished @ R,R erase-old-x
add-finished * L,L add-finished

erase-old-x x E,L,L print-new-x
erase-old-x z Py,L,L print-new-x
erase-old-x * R,R erase-old-x

print-new-x @ R,R erase-old-y
print-new-x y Pz find-digits
print-new-x ~ Px find-digits

erase-old-y y E,L,L print-new-y
erase-old-y * R,R erase-old-y

print-new-y @ R new-digit-is-one
print-new-y * Py,R reset-new-x

reset-new-x ~ R,Px flag-result-digits
reset-new-x * R,R reset-new-x

flag-result-digits s Pt,R,R unflag-result-digits
flag-result-digits v Pw,R,R unflag-result-digits
flag-result-digits * R,R flag-result-digits

unflag-result-digits s Pr,R,R unflag-result-digits
unflag-result-digits v Pu,R,R unflag-result-digits
unflag-result-digits * , find-digits

new-digit-is-zero @ R print-zero-digit
new-digit-is-zero * L new-digit-is-zero

print-zero-digit 0 R,E,R print-zero-digit
print-zero-digit 1 R,E,R print-zero-digit
print-zero-digit ~ P0,R,R,R cleanup

new-digit-is-one @ R print-one-digit
new-digit-is-one * L new-digit-is-one

print-one-digit 0 R,E,R print-one-digit
print-one-digit 1 R,E,R print-one-digit
print-one-digit ~ P1,R,R,R cleanup

cleanup ~ , new
cleanup * E,R,R cleanup
