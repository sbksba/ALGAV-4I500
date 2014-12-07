#!/bin/bash
echo "== Creation Graph =="
echo ""
echo "Graph : briandais.png "
./log/plot_tree.gp
echo "Graph : hybrid.png "
./log/plot_trie.gp
echo "Graph : timeAdd.png "
./log/plot_timeAdd.gp
echo "Graph : thread.png "
./log/plot_thread.pg
