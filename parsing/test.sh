echo "normal entry: 'echo test'"
echo test
echo
echo "space in the begining '       echo test'"
      echo test
echo
echo "pipes: 'echo test | echo test'"
echo test | echo test
echo
echo "pipe with no spaces 'echo test|echo test'"
echo test|echo test
echo
echo "test with 1 space left: 'echo test |echo test'"
echo test |echo test
echo
echo "test with 1 space right: 'echo test| echo test'"
echo test| echo test
echo
echo "test with space in argument 'echo test         test'"
echo test         test
echo
echo "test with space before argument: 'echo       test test'"
echo           test test
echo
echo "test with space after argument: 'echo test test       '"
echo test test
echo
echo "test with special characters: 'echo ''test         $(echo test)'' '"
echo "test         $(echo test)"
echo
echo "test with sigle quotation: 'echo ''test         $(echo test)'' '"
echo "test         $(echo test)"
echo
