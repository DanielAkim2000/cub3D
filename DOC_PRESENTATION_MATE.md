# cub3D - Guide de passation detaille

Objectif de ce document:

- donner une lecture claire du projet a une personne qui maitrise deja le parsing,
- expliquer en detail comment le code est organise,
- montrer comment les modules se branchent entre eux,
- permettre de presenter le projet a l oral sans zones floues.

## 1) Vue globale en 30 secondes

Pipeline complet:

1. main verifie les arguments.
2. parseur lit et valide le fichier .cub.
3. init initialise MLX, ecran, textures et sprites.
4. boucle de jeu:
   - inputs
   - update etats (portes + animations)
   - raycasting (murs)
   - sprites 3D (torches)
   - minimap
   - HUD arme + crosshair
5. fermeture propre (free complet).

Resultat:

- moteur 3D type Wolf3D,
- collisions,
- portes ouvrables,
- minimap,
- souris,
- sprites animes.

## 2) Fichiers et responsabilites

### 2.1 Entrypoint

- srcs/main.c
  - orchestre toute la vie du programme.

### 2.2 Parsing

- srcs/parser/parser.c: pipeline principal du parsing.
- srcs/parser/parser_line_utils.c: detection lignes map/identifiants + append map.
- srcs/parser/parser_identifiers.c: decode NO/SO/WE/EA/D/F/C.
- srcs/parser/parser_final_check.c: verification finale map + spawn joueur.
- srcs/parser/parser_map_items.c: regles de validite pour 0/T/D/spawn.
- srcs/parser/parser_map_utils.c: helpers .cub + dimensions map + caracteres.
- srcs/parser/parser_utils.c: helpers trim/blank/split.
- srcs/parser/parser_utils2.c: verif .xpm + taille xpm + alloc tableaux portes.
- srcs/parser/parser_error_utils.c + parser_free_utils.c: erreurs + free parser.

### 2.3 Initialisation / nettoyage

- srcs/init/init_mlx.c: mlx_init, window, image ecran, put pixel.
- srcs/init/init.c: init general + sprites + flags/timers.
- srcs/init/free_game_all.c: destruction globale runtime.

### 2.4 Runtime input / gameplay

- srcs/hooks/keys.c: key press/release, toggle porte, speed shift.
- srcs/hooks/mouse.c: rotation souris + tir (animation arme).
- srcs/hooks/move.c: collision + dispatcher de movement.
- srcs/hooks/move_walk.c: forward/back/strafe.
- srcs/hooks/move_rotate.c: rotation clavier.
- srcs/hooks/render.c: ordre d une frame.
- srcs/hooks/close_window.c: sortie propre.

### 2.5 Moteur rendu

- srcs/raycaster/raycast.c: boucle colonnes ecran.
- srcs/raycaster/dda.c: traverser la grille jusqu au hit.
- srcs/raycaster/draw.c: distance, hauteur, dessin colonne.
- srcs/textures/textures.c: load xpm, choix texture, coordonnees texture.
- srcs/textures/colors.c: lecture pixel texture.

### 2.6 Bonus rendu

- srcs/minimap/minimap.c + minimap_utils.c.
- srcs/sprites/sprites.c + sprites_draw.c + sprites_torch_draw.c.

## 3) Structures clefs et ce qu elles portent

### 3.1 t_game (includes/base.h)

t_game est la source de verite globale:

- pointeurs MLX (mlx, win),
- image ecran screen,
- textures world + sprites,
- map (char \*\*), width, height,
- etat joueur,
- etat rayon courant,
- couleurs sol/plafond,
- portes dynamiques:
  - door_target[y][x] entier (0/1),
  - door_open[y][x] double (ouverture progressive),
- zbuffer par colonne pour cacher/afficher correctement les sprites.

### 3.2 t_player

Contient:

- position,
- direction regard,
- plan camera,
- vitesses,
- flags input (avancer, reculer, strafe, rotate).

Le choix dir + plane est essentiel: c est ce qui permet de transformer la scene 2D en projection 3D par colonne.

### 3.3 t_ray

Structure temporaire reutilisee pour chaque colonne:

- direction rayon,
- case map courante,
- distances DDA,
- side touche,
- distance perpendiculaire,
- bornes verticales de dessin.

## 4) Cycle de vie exact du programme

### 4.1 main (srcs/main.c)

Ordre:

1. verifier argc == 2 sinon message usage.
2. ft_parse_file:
   - remplit game,
   - en cas echec, ft_free_game.
3. ft_init_game:
   - si echec, message erreur.
4. activer souris et hooks MLX.
5. masquer souris + centrer souris.
6. mlx_loop.

### 4.2 Hooks installes

- event 17: fermeture fenetre.
- loop hook: ft_render_frame.
- key press + key release.
- mouse press.

Important: la logique continue est dans ft_render_frame, pas dans les callbacks de touche (les callbacks posent surtout des flags).

## 5) Parsing detaille, fonction par fonction

## 5.1 parser.c - orchestration

ft_parse_file_helper:

- reset m et g avec bzero,
- verifie chemin .cub,
- ouvre fichier,
- lit toutes les lignes,
- delegue chaque ligne a ft_parse_line.

ft_parse_file:

- refuse map absente,
- refuse identifiants manquants,
- lance ft_final_check,
- re-ouvre chaque texture declaree pour verifier format xpm 64x64,
- copie m.map vers g.map,
- calcule map_width/map_height,
- alloue door_target et door_open via ft_init_doors.

Point important:

- ID_D est optionnel dans le comptage obligatoire,
- mais devient obligatoire si une porte D existe dans la map (controle en final check).

## 5.2 parser_line_utils.c - detection du contexte

ft_parse_line:

- trim line,
- si on n est pas encore dans la map:
  - ligne vide: ignore,
  - si ce n est pas une ligne de map: parse identifiant,
  - sinon: debut map.
- si on est deja dans la map:
  - ligne vide interdite,
  - ligne doit rester une ligne de map,
  - append dans le tableau dynamique m.map.

Interpretation:

- le parseur force la map a etre le dernier bloc,
- empeche des identifiants qui arrivent apres le debut de map.

## 5.3 parser_identifiers.c - lecture des champs de config

ft_get_identifier_type convertit texte -> enum.

ft_parse_id_helper applique les regles:

- identifiant connu,
- pas de doublon,
- pas depassement logique,
- parsing RGB pour F et C.

ft_parse_identifier:

- split ligne en id + value,
- si texture: verifie chemin .xpm ouvrable puis strdup dans tex_paths[type],
- met seen[type] a 1,
- incremente id_count sauf pour D.

## 5.4 parser_final_check.c + parser_map_items.c

ft_final_check parcourt toute la grille et applique ft_final_check_loop.

Cas 0 et T:

- ft_floor_check verifie que les 4 voisins ne sont pas vides.

Cas joueur N/S/E/W:

- ft_set_player initialise:
  - pos (centre de case, +0.5),
  - dir,
  - plane.
- ft_player_check impose unicite et fermeture locale.
- case map remplacee par 0 (important pour le moteur runtime).

Cas porte D:

- ft_door_check:
  - porte non collee au vide,
  - porte alignee horizontalement ou verticalement,
  - et coherent avec cellules walkable autour.

Post conditions de ft_final_check:

- exactement 1 joueur,
- si au moins une porte detectee alors identifiant D present.

## 5.5 parser_utils2.c - xpm et portes

ft_texture_path_checker:

- extension .xpm,
- fichier lisible.

ft_xpm_size_checker:

- lit le fichier xpm jusqu a la ligne metadata,
- extrait width/height,
- impose 64x64.

ft_init_doors:

- alloue deux tableaux 2D:
  - int \*\*door_target,
  - double \*\*door_open.
- tailles basees sur map_height/map_width.

## 6) Pourquoi le parsing simplifie le runtime

Le runtime suppose des invariants forts deja garantis:

- map fermee,
- spawn unique,
- textures existantes,
- map nettoyee de N/S/E/W (devenus 0),
- tableau portes deja alloue.

Grace a ces invariants:

- moins de checks defensifs dans DDA,
- collisions plus simples,
- moins de risques de crash en boucle frame.

## 7) Initialisation MLX et assets

## 7.1 init_mlx.c

ft_init_mlx:

- mlx_init,
- mlx_new_window(WIDTH, HEIGHT),
- ft_init_screen (mlx_new_image + mlx_get_data_addr).

ft_put_pixel ecrit dans le buffer image (pas directement dans window).

## 7.2 init.c

ft_init_game:

- init mlx,
- load textures world,
- load sprites arme,
- load sprites torches,
- init vitesses player,
- reset flags touches,
- reset timers animation.

## 8) Frame loop en detail

Ordre exact dans ft_render_frame:

1. lire flags mouvement et deplacer joueur,
2. appliquer look souris si active,
3. avancer animation arme,
4. avancer animation torches,
5. mettre a jour ouverture des portes vers target,
6. lancer raycasting murs + floor + ceiling,
7. dessiner torches 3D,
8. dessiner minimap,
9. dessiner arme HUD,
10. dessiner crosshair,
11. pousser image sur la fenetre.

Observation technique:

- ft_raycast fait deja un mlx_put_image_to_window, puis ft_render_frame en refait un.
- cela ne casse pas le rendu, mais c est un point possible de nettoyage/optimisation.

## 9) Deplacement et collision, lecture fine

## 9.1 keys.c

Press:

- met les flags mouvement,
- ESC ferme,
- E toggle porte frontale,
- L toggle mouse enable,
- SHIFT augmente move_speed.

Release:

- remet flag a 0,
- SHIFT remet move_speed normale.

## 9.2 move_walk.c

ft_try_move applique resolution axe par axe:

- test X avec ancien Y,
- test Y avec ancien X.

Avantage:

- meilleur glissement le long des murs,
- moins de blocage diagonal brutal.

## 9.3 move.c

ft_check_collision teste 4 coins du joueur avec marge MARGIN.

ft_is_blocking:

- mur 1 bloque,
- porte D bloque tant que door_open < DOOR_BLOCK_THRESHOLD.

Conclusion gameplay:

- une porte presque ouverte peut encore bloquer,
- seuil tres proche du max pour eviter de traverser trop tot.

## 10) Rotation clavier et souris

## 10.1 Rotation clavier (move_rotate.c)

Rotation par matrice 2D sur:

- dir,
- plane.

Sans cette double rotation (dir + plane), la projection camera serait incoherente.

## 10.2 Souris (mouse.c)

ft_handle_mouse:

- lit position actuelle,
- calcule delta_x par rapport au centre,
- convertit en angle,
- applique rotation,
- recentre la souris.

Effet:

- relative mouse look continu.

## 11) Raycasting et DDA, pas a pas

## 11.1 raycast.c

Pour chaque colonne x:

- ft_init_ray,
- ft_init_dda,
- ft_perform_dda,
- ft_calculate_perp_dist,
- ft_calculate_wall_height,
- zbuffer[x] = distance,
- ft_draw_column.

## 11.2 dda.c

ft_init_dda calcule:

- delta_dist_x/y,
- step_x/y,
- side_dist_x/y initial.

ft_perform_dda boucle:

- avance dans la grille sur l axe le plus proche,
- detecte mur 1,
- ou gere porte D via:
  - orientation porte,
  - test de hit selon fraction d ouverture.

Point cle:

- porte consideree comme obstacle partiel,
- pas un simple switch binaire ouvert/ferme.

## 11.3 draw.c

ft_calculate_perp_dist:

- formule differente pour mur et porte,
- utilise distance perpendiculaire (evite fish-eye).

ft_calculate_wall_height:

- line_height = HEIGHT / distance,
- calcule draw_start/draw_end,
- clamp ecran.

ft_draw_column:

- y < draw_start: plafond,
- draw_start..draw_end: echantillonnage texture,
- > draw_end: sol.

## 12) Textures

## 12.1 Chargement (textures.c)

ft_load_xpm charge NO/SO/WE/EA.
ft_load_door_xpm charge texture porte si path present.

En cas d echec de load:

- message explicite,
- free global,
- exit(1).

## 12.2 Choix texture mur

ft_get_wall_texture_num:

- si cellule D -> texture porte,
- sinon choix selon side et signe direction rayon.

## 12.3 Coordonnee texture X

ft_get_wall_x calcule la position fractionnaire sur le mur.
ft_get_tex_x:

- convertit en index pixel X,
- inverse eventuellement selon orientation,
- applique offset d ouverture pour porte.

## 13) Portes: logique complete

Donnees:

- target binaire,
- open continue en double.

Input:

- E cherche la case devant le joueur (distance 1.5) et toggle target.

Animation frame:

- open approche target avec DOOR_SLIDE_SPEED,
- clamp entre 0 et DOOR_MAX_OPEN.

Consommation de cet etat:

- collision,
- DDA/hit,
- decalage texture porte,
- couleur minimap.

Donc la porte est une fonctionnalite transverse qui touche plusieurs modules.

## 14) Minimap detail

minimap.c:

- calcule centre fixe de la minimap,
- dessine fond,
- dessine les tuiles autour du joueur,
- dessine joueur + direction,
- dessine bordure.

minimap_utils.c:

- clipping strict dans le cadre minimap,
- couleur cellule selon type et etat porte.

## 15) Sprites detail

## 15.1 Arme HUD

sprites.c:

- load weapon_idle.xpm et weapon_fire.xpm,
- update timer/tick.

sprites_draw.c:

- choisit sprite actif selon phase animation,
- scale sprite a une taille proportionnelle a HEIGHT,
- ignore pixels transparents (magenta/noir).

## 15.2 Torches 3D

sprites.c:

- charge 4 frames torch_0..3,
- update frame cyclique.

sprites_torch_draw.c:

- pour chaque T sur la map:
  - transforme position monde -> espace camera,
  - projette en x ecran,
  - calcule largeur/hauteur sprite,
  - dessine colonnes visibles si plus proches que zbuffer.

Ce test zbuffer est la cle pour ne pas voir la torche a travers les murs.

## 16) Gestion memoire et fermeture

Parsing stage:

- ft_free_game,
- ft_free_parser_and_error,
- ft_map_free,
- ft_free_doors.

Runtime stage:

- ft_free_game_all:
  - destroy images (textures, sprites, screen),
  - destroy window,
  - destroy display,
  - free tableaux map et portes,
  - free mlx.

Point audit:

- le code nettoie proprement sur fermeture normale,
- et aussi sur plusieurs chemins d erreur de chargement.

## 17) Checklist de presentation orale (version detaillee)

1. Commencer par le schema global:
   - parse -> init -> loop.
2. Montrer que le parsing n est pas cosmetique:
   - il construit des invariants runtime.
3. Expliquer une frame complete dans render.c.
4. Zoom DDA:
   - comment on avance case par case,
   - comment une porte est testee.
5. Zoom collision:
   - marge + seuil de porte.
6. Zoom sprites:
   - zbuffer pour l occlusion.
7. Finir sur la proprete:
   - erreurs explicites,
   - liberation memoire.

## 18) Ce que ton mate parsing peut dire pour valoriser sa partie

Message fort:

- Le parsing impose une geometrie et une config coherentes avant runtime.
- Le moteur n a pas a gerer en permanence des cas invalides.
- Les choix parsing (caracteres autorises, unicite joueur, portes valides, textures 64x64) influencent directement:
  - la stabilite,
  - la simplicite du DDA,
  - la qualite du rendu,
  - la robustesse de la soutenance.

Traduction simple:

- sans un parsing strict, le moteur raycasting est fragile.
- avec ce parsing, le runtime est previsible et defendable techniquement.
