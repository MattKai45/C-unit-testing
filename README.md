# C Unit Testing with Ceedling

A template repository for writing and running C unit tests using [Ceedling](https://github.com/ThrowTheSwitch/Ceedling), with automated test execution via GitHub Actions on every push or pull request to `main`.

## What's included

- **Ceedling** — test-centered build system for C, using Unity as the test framework and CMock for mocking
- **gcov** — code coverage reporting via gcovr
- **GitHub Actions** — CI workflow that runs all tests automatically on push/PR to `main`

## Project structure

```
├── src/                  # Production source files (.c and .h)
├── test/                 # Test files (prefix: test_)
│   └── support/          # Test support files (helpers, fixtures)
├── build/                # Generated build artifacts (not committed)
├── project.yml           # Ceedling configuration
└── .github/workflows/
    └── ceedling.yml      # CI workflow
```

## Running tests locally

### Prerequisites

- Ruby (3.3.6 recommended)
- GCC
- gcovr (for coverage reports)

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

Coverage reports are generated in `build/artifacts/gcov/`.

## Adding a new module

1. Create `src/MyModule.c` and `src/MyModule.h`
2. Create `test/test_MyModule.c` with your Unity test cases
3. Run `ceedling test:all`

Ceedling automatically discovers source and test files — no manual build configuration needed.

## CI / GitHub Actions

The workflow in [.github/workflows/ceedling.yml](.github/workflows/ceedling.yml) triggers on every push and pull request to `main`. It:

1. Checks out the repository
2. Sets up Ruby 3.3.6
3. Installs Ceedling
4. Runs `ceedling test:all`

A failed test causes the workflow to fail, blocking merges until the tests pass.
