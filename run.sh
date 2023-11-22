timeout 4 ./tester.sh 

printf "SERV:\n" 
while IFS= read -r line; do
  printf "\t%s\n" "${line}"
done < ".tester/serv.out"

printf "CLI_A:\n"
while IFS= read -r line; do
  printf "\t%s\n" "${line}"
done < ".tester/cli_a.out"

printf "CLI_B:\n" 
while IFS= read -r line; do
  printf "\t%s\n" "${line}"
done < ".tester/cli_b.out"

printf "CLI_C:\n" 
while IFS= read -r line; do
  printf "\t%s\n" "${line}"
done < ".tester/cli_c.out"

