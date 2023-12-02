#!/bin/bash

# Server


readonly CHANNEL_NAME="#A"

readonly TEST_A=$(cat << __EOF__
/JOIN #B
/MODE #B +i
$(sleep 1)
/INVITE xelor #B

__EOF__
)

readonly TEST_B=$(cat << __EOF__
$(sleep 2)
/JOIN #B

__EOF__
)

readonly TEST_C=$(cat << __EOF__
$(sleep 3)
/JOIN #B
__EOF__
)



readonly PROG="ircserv"
readonly PORT=7771
readonly PASS="coucou"
readonly OUTDIR=".tester"

readonly  SERV_OUTFILE="${OUTDIR}/serv.out"
readonly CLI_A_OUTFILE="${OUTDIR}/cli_a.out"
readonly CLI_B_OUTFILE="${OUTDIR}/cli_b.out"
readonly CLI_C_OUTFILE="${OUTDIR}/cli_c.out"

function __launchServ {
  ./"${PROG}" "${PORT}" "${PASS}" &> "${SERV_OUTFILE}"
}

function __launchClientA {
  local NICK="xel"
  touch ${CLI_A_OUTFILE}

  nc localhost "${PORT}" << __EOF__ &> "${CLI_A_OUTFILE}"
/PASS ${PASS}
/NICK ${NICK}
/USER l a a :b

${TEST_A}
__EOF__
}

function __launchClientB {
  local NICK="xelor"
  touch ${CLI_B_OUTFILE}

  nc localhost "${PORT}" << __EOF__ &> "${CLI_B_OUTFILE}"
/PASS ${PASS}
/NICK ${NICK}
/USER l a a :b

${TEST_B}
__EOF__
}

function __launchClientC {
  local NICK="polo"
  touch ${CLI_C_OUTFILE}

  nc localhost "${PORT}" << __EOF__ &> "${CLI_C_OUTFILE}"
/PASS ${PASS}
/NICK ${NICK}
/USER l a a :b

${TEST_C}
__EOF__
}

function __main {

  mkdir -vp "${OUTDIR}"

  __launchServ &
  printf "[+] Started ${PROG} at pid (%s)\n" "$(pgrep "${PROG}")"
  sleep 1

  __launchClientA &
  printf "[+] client A\n"

  __launchClientB &
  printf "[+] client B\n"

  __launchClientC &
  printf "[+] client C\n"


  wait 
}

__main
