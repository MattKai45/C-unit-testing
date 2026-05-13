# C Unit Testing with Ceedling

[![CI](https://github.com/MattKai45/C-unit-testing/actions/workflows/ceedling.yml/badge.svg)](https://github.com/MattKai45/C-unit-testing/actions/workflows/ceedling.yml)
[![Coverage](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/MattKai45/REPLACE_WITH_GIST_ID/raw/coverage.json)](https://github.com/MattKai45/C-unit-testing/actions/workflows/ceedling.yml)

A template repository for writing and running C unit tests using [Ceedling](https://github.com/ThrowTheSwitch/Ceedling), with automated test execution and coverage reporting via GitHub Actions on every push or pull request to `main`.

## What's included

- **Ceedling** — test-centered build system for C, using Unity as the test framework and CMock for mocking
- **gcov + gcovr** — code coverage instrumentation and HTML/JSON report generation
- **GitHub Actions** — CI workflow that runs all tests, measures coverage, and uploads an HTML report artifact on every push/PR to `main`

## Project structure

```
├── src/                  # Production source files (.c and .h)
├── test/                 # Test files (prefix: test_)
│   └── support/          # Test support files (helpers, fixtures)
├── build/                # Generated build artifacts (not committed)
│   └── artifacts/gcov/   # Coverage HTML report output
├── project.yml           # Ceedling configuration
└── .github/workflows/
    └── ceedling.yml      # CI workflow
```

## Running tests locally

### Prerequisites

- Ruby 3.3.6
- GCC
- gcovr (`pip install gcovr`)

```sh
gem install ceedling
```

### Run all tests

```sh
ceedling test:all
```

### Run tests with coverage

```sh
ceedling gcov:all
```

This generates an HTML coverage report at `build/artifacts/gcov/`. In CI the report is also uploaded as a workflow artifact — find it on the Actions run page under **Artifacts**.

## Adding a new module

1. Create `src/MyModule.c` and `src/MyModule.h`
2. Create `test/test_MyModule.c` with your Unity test cases
3. Run `ceedling test:all`

Ceedling automatically discovers source and test files — no manual build configuration needed.

## CI / GitHub Actions

The workflow in [.github/workflows/ceedling.yml](.github/workflows/ceedling.yml) triggers on every push and pull request to `main`. It:

1. Checks out the repository
2. Sets up Ruby 3.3.6 and installs Ceedling
3. Installs gcovr
4. Runs `ceedling gcov:all` (tests + coverage in one step)
5. Generates a JSON coverage summary and updates the coverage badge
6. Uploads the HTML coverage report as a downloadable artifact

A failed test causes the workflow to fail, blocking merges until tests pass.

## Badge setup (one-time)

The coverage badge requires two one-time steps:

**1. Create a GitHub Gist**

Go to [gist.github.com](https://gist.github.com), create a new public gist with any filename (e.g. `coverage.json`) and any content. Copy the Gist ID from the URL: `gist.github.com/<username>/<GIST_ID>`.

**2. Create a Personal Access Token**

Go to **GitHub Settings → Developer settings → Personal access tokens → Tokens (classic)** and create a token with the `gist` scope. Add it to this repo as a secret named `GIST_SECRET` (**Settings → Secrets and variables → Actions**). Add the Gist ID as a secret named `GIST_ID`.

**3. Update the badge URL in this README**

Replace `REPLACE_WITH_GIST_ID` in the badge URL at the top of this file with your actual Gist ID.

After the first successful CI run on `main`, the badge will show the live coverage percentage and color (green ≥ 90%, yellow ≥ 75%, red below 75%).
