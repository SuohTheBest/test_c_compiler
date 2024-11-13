from subprocess import run, PIPE, TimeoutExpired
import re, os, argparse


parser = './parser'
group = 0
advance = False
wait = False
timeout = 1.0
more = False
color_option = 'auto'
result = {'AC': 0, "FalsePositive": 0, 'WA': 0, 'RE': 0, 'TLE': 0, 'total': 0}


def main():
  global parser, group, advance, wait, timeout, more, color_option
  arg = argparse.ArgumentParser()
  arg.add_argument('-p', '--parser', default='./parser', help='location of parser')
  arg.add_argument('-g', '--group', default=0, type=int, help='group number')
  arg.add_argument('-a', '--advance', action='store_true', help='do advance tests')
  arg.add_argument('-w', '--wait', action='store_true', help='wait after WA')
  arg.add_argument('-t', '--timeout', default=1.0, type=float, help='time limit for one test')
  arg.add_argument('-m', '--more', action='store_true', help='agree more report than ans, only for advance test')
  arg.add_argument('--color', choices=["never", "always", "auto"], default="auto", help="never, always, or auto")
  args = arg.parse_args()
  parser = args.parser
  group = args.group
  advance = args.advance
  wait = args.wait
  timeout = args.timeout
  more = args.more
  color_option = args.color
  test_dir('base')
  for dir in os.listdir('extend'):
    if (group == 0 and not dir.startswith('not')) or dir == str(group) or \
       (group != 0 and dir.startswith('not') and dir != f'not{group}'):
      test_dir(os.path.join('extend', dir))
  if advance:
    test_advance()
  print(', '.join([f'{i}: {j}' for i, j in result.items() if j > 0]))


def getsub(file: str):
  return x[1] if len(x := file.rsplit('.', 1)) > 1 else ''


def chsub(file: str, sub: str):
  return file.rsplit('.', 1)[0] + '.' + sub


def pause():
  if wait:
    a = input('Input [c] to continue, [q] to quit: ')
    if not a[:1].lower() == 'c':
      exit()


COLORS = {"default": "\033[0m", "red": "\033[31m", "green": "\033[32m", "yellow": "\033[33m"}


def color(name: str, text: str):
  if color_option == "always" or (color_option == "auto" and os.isatty(1)):
    return COLORS[name] + text + COLORS["default"]
  return text


def get_ans(file: str):
  ans, newans = [[]], []
  with open(chsub(file, 'txt')) as fp:
    for line in fp:
      newans = []
      if line and line[0] == ' ':
        newans.extend(ans)
      for token in line.split():
        newans.extend([x + token.split(',') for x in ans])
      ans = newans
  return ans


def analyse_out(output: str):
  err = []
  for line in output.splitlines():
    res = re.match("Error type (A|B|\d+) at Line (\d+)", line, re.I)
    if res:
      err.append((int(res[2]), int(res[1]) if res[1].isdecimal() else {'A': -1, 'B': -2}[res[1]]))
  return [f"{y if y >= 0 else ' AB'[-y]}-{x}" for x, y in sorted(set(err))]


def run_one(file: str):
  try:
    p = run([parser, file], stdin=PIPE, stdout=PIPE, stderr=PIPE, text=True, encoding="utf-8", timeout=timeout)
  except TimeoutExpired:
    print(f"[{file}] {color('red', 'TLE')}")
    return 'TLE'
  if p.returncode != 0:
    print(f"[{file}] {color('red', 'RE')}")
    return 'RE'
  return p


def test_one(file: str):
  p = run_one(file)
  if isinstance(p, str):
    return p
  ans = get_ans(file)
  err = analyse_out(p.stdout)
  if err in ans:
    print(f"[{file}] {color('green', 'AC')}")
    return 'AC'
  elif (nearest := max([i for i in ans if set(i).issubset(err)] + [[]], key=len)) != []:
    print(f"[{file}] {color('yellow', 'FalsePositive')}: got {err}, should NOT report {[i for i in err if i not in nearest]}")
    return 'FalsePositive'
  else:
    print(f"[{file}] {color('red', 'WA')}: got {err}, expect {ans[0]}")
    return 'WA'


def test_dir(dir: str):
  for path, _, files in os.walk(dir):
    for file in sorted(filter(lambda x: getsub(x) == 'cmm', files)):
      file = os.path.join(path, file)
      result['total'] += 1
      r = test_one(file)
      result[r] += 1
      if r != 'AC':
        pause()


def test_advance_one(file: str):
  p = run_one(file)
  if isinstance(p, str):
    return p
  with open(chsub(file, 'output')) as fp:
    ans = fp.read()
  anserr = analyse_out(ans)
  outerr = analyse_out(p.stdout)
  if more:
    ac = set(anserr).issubset(outerr)
    false_positive = False
  else:
    ac = set(anserr) == set(outerr)
    false_positive = set(anserr).issubset(outerr)
  if ac:
    print(f"[{file}] {color('green', 'AC')}")
    return 'AC'
  elif false_positive:
    print(f"[{file}] {color('yellow', 'FalsePositive')}: got {outerr}, should NOT report {[i for i in outerr if i not in anserr]}")
    return 'FalsePositive'
  else:
    print(f"[{file}] {color('red', 'WA')}: got {outerr}, expect {anserr}")
    return 'WA'


def test_advance():
  for path, _, files in os.walk('advance'):
    for file in sorted(filter(lambda x: getsub(x) == 'cmm', files)):
      file = os.path.join(path, file)
      result['total'] += 1
      r = test_advance_one(file)
      result[r] += 1
      if r != 'AC':
        pause()


if __name__ == "__main__":
  main()
