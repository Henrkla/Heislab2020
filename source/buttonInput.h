/**@file
  *@brief Tar input signalene til knappene og legger dem inn i et array
  */

/** @brief Sjekker alle knappene og oppdaterer arrayet med aktive knapper
  */
void button_fetch_inputs();

/** @brief Forteller om en spesefikk knapp er trykket inn eller ikke
  *
  *@param[in] button Knappen vi spør om er trykket på
  *@param[in] floor Etasjen hvor knappen er
  *@return Er knappen vi lurer på trykket inn (t/f) = (1/0)
  */
int button_input_array_check()