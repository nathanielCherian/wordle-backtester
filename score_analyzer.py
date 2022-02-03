from matplotlib import pyplot as plt

vals = []
with open("score.txt") as f:
    lines = f.readlines()
    vals = [int(l) for l in lines]

vals.sort()

plt.xlim([min(vals)-5,500])


plt.hist(vals, bins=1000, alpha=0.5)
plt.title('Wordle Data')
plt.xlabel('possible words after 3 guesses')
plt.ylabel('count')

plt.savefig('score.png')
