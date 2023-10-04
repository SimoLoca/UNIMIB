I file contenenti il codice sono:
	- [-] FlowerRecognition_project.ipynb -> la prima parte
	- [-] FlowerRecognition_project_HyperparameterTuning.ipynb -> la seconda parte

Vi sono poi report e presentazione:
	- [-] report.pdf -> il report in formato pdf
	- [] presentazione.pdf -> la presentazione in formato pdf

All'interno della cartella vi è poi la cartella "flowers", al cui interno vi sono:
	- [] il dataset di immagini -> cartella "jpg"
	- [] i 3 file di base per creare gli split del dataset, nomi delle labels e indici ->
		"imagelabels.mat", "labels_to_names.json" e "setid.mat"
	- [] gli split creati del dataset -> "train", "valid" e "test"
	- [] le features estratte durante il progetto -> cartella "features"
	- [] i modelli fine-tunati nelle rispettive cartelle -> "fine_tuned_densenet_allFreezed" e
		"fine_tuned_densenet_NOFreezed"
	- [] la cartella "keras_tuner" che contiene i parametri ottenuti in fase di ottimizzazione della rete
	- [] la cartella "tuned_model" col modello ottimizzato
