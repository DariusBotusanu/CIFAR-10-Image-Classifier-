Clasificatorii sunt antrenati si evaluati inauntrul unei instante Statistics.
O instanta "Statistics" salveaza detalii despre clasificator intr-un csv.
Detaliile sunt: - confusion matrix
		     - accuracy (%)
		     - elapsed time(seconds)
elapsed time masoara timpul total pentru antrenarea si evalaurea clasificatorului.

KNN consuma mult timp pentru toate cele 10000 de imagini din testBatch, statisticile aratate pentru knn sunt pentru primele 100 de imagini.
Solutii incercate:
	- reimplementarea evaluarii unei singure imagini folosing
	un vector care are primii k vecini la inceput (sortat 	partial cu buble sort aplicat de k ori), dar devine si 	mai incet (in medie cu 500 secunde mai incet)
