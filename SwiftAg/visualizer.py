import sys
import pygame
import json

file = open(sys.argv[1])
fs = file.read()
edges = json.loads(fs)

pygame.init()
screen = pygame.display.set_mode([1024,768])
screen.fill((0,0,0))

for e in edges:
	pygame.draw.circle(screen, (255,255,255), [e[0][0], e[0][1]], 3)
	pygame.draw.circle(screen, (255,255,255), [e[1][0], e[1][1]], 3)
	pygame.draw.line(screen, (0,255,0), [e[0][0], e[0][1]], [e[1][0], e[1][1]])

pygame.display.update()	

while True:
	events = pygame.event.get()
	for e in events:
		if e.type == pygame.KEYDOWN:
			sys.exit()