#!/bin/bash

DATAVIZ_WINDOW_INDEX=0
ROW_COUNT=6
MY_ROW=$((RANDOM % $ROW_COUNT))
MY_ANSWER=$((RANDOM % 100))
ALL_VALUES=() # array
TITLES=("Québécoise" "Canadienne" "Autochtone" "Américaine" "Européenne" "Autre")

for i in {1..6};
do
  ALL_VALUES+=($((RANDOM % 100)))
done

set -o verbose

oscsend osc.udp://localhost:31337 /dataviz/${DATAVIZ_WINDOW_INDEX}/view_answer_by_culture iiisisisisisisi \
  $ROW_COUNT \
  $MY_ROW \
  $MY_ANSWER \
  ${TITLES[0]} \
  ${ALL_VALUES[0]} \
  "${TITLES[1]}" \
  ${ALL_VALUES[1]} \
  "${TITLES[2]}" \
  ${ALL_VALUES[2]} \
  "${TITLES[3]}" \
  ${ALL_VALUES[3]} \
  "${TITLES[4]}" \
  ${ALL_VALUES[4]} \
  "${TITLES[5]}" \
  ${ALL_VALUES[5]}

