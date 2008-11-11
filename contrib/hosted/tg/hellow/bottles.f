      program ninetynine
      implicit none
      integer i

      do i=99,1,-1
        print*, i,' bottles of beer on the wall, ',i,' bottles of beer'
        print*, 'take one down, pass it around, ',i-1,
     .       ' bottles of beer on the wall'
      enddo
      end
