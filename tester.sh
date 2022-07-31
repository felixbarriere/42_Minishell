#! /bin/sh


echo ---Ce tester ne gere pas: EXIT, RETURN VALUES, SIGNALS, EXPORT, RELATIVE PATH, Env PATH ----
echo \n
echo ---------- Simple Command and Global -----------
/bin/ls
          
'           '
""
       ""
echo \n
#echo:
echo ---------- ECHO -----------
echo bonjour
echo bonjour les gens
echo -n bonjour les gens
echo -nnnnnnnnnnnnnn bonjour les gens
echo -n-n-n-n-n bonjour 
echo -n -n -n bonjour
echo -n bonjour -n
echo -nnnnnnnnm bonjour
echo “” “” “” bonjour

echo \n
echo ---------- DOUBLE QUOTES -----------
echo “hello les gens”
ca”t main.c”


echo ---------- SIMPLE QUOTES -----------
echo “$USER”’$USER’ “$SHELL ‘$USER’”
echo ‘echo bonjour >> test.txt’
echo ' cat | echo hh | pwd|'


echo ---------- PWD -----------
pwd


echo ---------- REDIRECTION sauf heredocs -----------
echo bonjour >> test.txt
echo salut > test.txt
echo salut >> test.txt >> autre.txt


echo --------- PIPES SIMPLES -----------
cat | cat | ls
ls | grep .c
ls | wc -l
cd | echo bonjour
echo toto | cat
echo felix | ghjk | echo
echo felix | ghjk | unset tes-es
echo felix | hgf | unset gfg-g
