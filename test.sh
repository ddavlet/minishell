#!bin/sh
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
echo "testing argument asignment: 'ARG='test' | echo \$ARG'"
ARG='test' | echo $ARG
echo
echo "testing argument asigment first then echo: 'ARG='test' \n echo \$ARG'"
ARG='test'
echo $ARG
echo
echo "testing name of command in quotations: ' 'echo' test'"
"echo" test
echo
echo "testing name of command in quotations: ' 'echo' test'"
'echo' test
echo
echo "testing double quotatin inside single qoutation: ' echo ' ''test'' ' '"
echo ' "test" '
echo
echo "testing single quotatin inside double qoutation: ' echo '' 'test' '' '"
echo " 'test' "
echo
echo "testing single quotatin inside signle qoutation: ' echo ' 'test' ' '"
echo ' 'test' '
echo
echo "testing double quotatin inside double qoutation: ' echo '' ''test'' '' '"
echo " "test" "
echo
echo "complex quotations"
echo """'"'"test"'"'"""
'e'c''h''o'' tes't'
"ec"h"o" 'te's't'
echo
echo "testing echo with space after $ sign: 'echo test$ test'"
echo test$ test
