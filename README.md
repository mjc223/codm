# Curse of Death Mountain

## Build Instructions:

You will need to obtain the libraries required by the source code
 - SDL2
 - SDL2_image
 - SDL2_mixer
 - SDL2_ttf

There are additional sub modules that are needed for this project to work as well, under normal circumstances they could be pulled directly from
the project, but the git submodule updater failed to work as anticipated.
This is the command: `git submodule update --init --recursive`

Instead, run `git pull [repo]` within each submodule. Namely the modules of
 - GFC
 - Simple_Logger
 - Simple_Json

After this, go into every submodules src directories and type `make` `make static`, in the deepest modules first, until all are built.


A `gf2d` binary will be created within the root of the git repository.

## Summary:
Curse of Death Mountain is a Legend of Zelda (NES) inspired game, featuring varied enemies, dungeons, environments, and interactions, while remaining simplistic enough to be akin to the source material.

This project was forked for my 2D Game Development course (credit to Professor DJ Kehoe), and also takes loose inspiration from Zelda Classic, a popular Windows recreation of the original Legend of Zelda.

## Known Issues:

## Features:

## How to test each deliverable: