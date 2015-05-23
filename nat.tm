# from The Annotated Turing, page 112
# prints all natural numbers from 0 onwards
begin ~ P0 increment
increment 0 P1 rewind
increment 1 P0,L increment
increment ~ P1 rewind
rewind ~ L increment
rewind 0 R rewind
rewind 1 R rewind
