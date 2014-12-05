#!/bin/bash
#gui.sh

ans=$(zenity --list --text "Choisissez votre option : " --radiolist --column "" --column "Option" FALSE "test Briandais" FALSE "test hybride" FALSE "plot");
echo $ans;

case $ans in
    "test Briandais")
	./bin/BRIANDAIS;;

    "test hybride")
	./bin/HYBRID;;

    "plot")
	pl=$(zenity --list --text "Choisissez votre option : " --radiolist --column "" --column "Option" FALSE "file" FALSE "directory");
	echo $pl;
	
	case $pl in
	    "file")
		FILE=`zenity --file-selection --title="Selectionnez un fichier"`
		case $? in
		    0)
			./bin/PLOTBRIANDAIS F $FILE > log/briandais.dat
			./bin/PLOTHYBRID $FILE > log/hybrid.dat
			;;
		    1)
			echo "Aucun fichier est selectionne";;
		    -1)
			zenity --error;;
		esac
		;;
	    
	    "directory")
		DIR=`zenity --file-selection --directory --title="Selectionnez un repertoire"`
		case $? in
		    0)
			./bin/PLOTBRIANDAIS D $DIR > log/briandais.dat
			./bin/PLOTHYBRID D $DIR > log/hybrid.dat
			`pwd`
			`cd log`
			./plot_tree.gp
			./plot_trie.gp
			evince briandais.png
			;;
		    1)
			echo "Aucun repertoire est selectionne";;
		    -1)
			zenity --error;;
		esac
		;;
	esac
esac
