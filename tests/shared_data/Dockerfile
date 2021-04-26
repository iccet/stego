FROM mcr.microsoft.com/dotnet/core/runtime:3.1 AS base
WORKDIR /app

FROM mcr.microsoft.com/dotnet/core/sdk:3.1 AS build
WORKDIR /src
COPY ["SharedData.csproj", "SharedData/"]
RUN dotnet restore "SharedData/SharedData.csproj"
COPY . .
WORKDIR "/src/SharedData"
RUN dotnet build "SharedData.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "SharedData.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "SharedData.dll"]
