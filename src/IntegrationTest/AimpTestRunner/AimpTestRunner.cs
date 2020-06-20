﻿// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using System.Diagnostics;
using System.IO;
using System.Xml;
using AIMP.SDK;
using AIMP.SDK.MessageDispatcher;
using Aimp.TestRunner.Engine;
using Aimp.TestRunner.UnitTests;
using NUnit.Engine;

namespace Aimp.TestRunner
{
    [AimpPlugin("AimpTestRunner", "Evgeniy Bogdan", "1", AimpPluginType = AimpPluginType.Addons)]
    public class AimpTestRunnerPlugin : AimpPlugin, ITestEventListener
    {
        public class Hook : IAimpMessageHook
        {
            private readonly Func<AimpCoreMessageType, int, int, ActionResultType> _hook;

            public Hook(Func<AimpCoreMessageType, int, int, ActionResultType> hook)
            {
                _hook = hook;
            }

            public ActionResultType CoreMessage(AimpCoreMessageType message, int param1, int param2)
            {
                return _hook(message, param1, param2);
            }
        }

        private ITestEngine _engine;
        private TextWriter _writer;
        private bool _inProgress;

        public override void Initialize()
        {
            var path = Path.Combine(Player.Core.GetPath(AimpCorePathType.AIMP_CORE_PATH_PLUGINS), "AimpTestRunner");

            AppDomain.CurrentDomain.SetData("APPBASE", path);
            Environment.CurrentDirectory = path;

            _engine = TestEngineActivator.CreateInstance();
            _engine.WorkDirectory = path;
            _engine.Initialize();
            TestPackage package = new TestPackage(Path.Combine(path, "AimpTestRunner_plugin.dll"));
            System.Diagnostics.Debug.WriteLine(AppDomain.CurrentDomain.FriendlyName);
            package.Settings.Add("ProcessModel", "Single");
            ITestRunner runner = _engine.GetRunner(package);

            AimpTestContext.Instance.AimpPlayer = Player;
            _writer = new StreamWriter(Path.Combine(path, "test_output.log"));

            Player.ServiceMessageDispatcher.Hook(new Hook((type, i, arg3) =>
            {
                if (type == AimpCoreMessageType.AIMP_MSG_EVENT_LOADED && !_inProgress)
                {
                    _inProgress = true;
                    XmlNode testResult = runner.Run(this, TestFilter.Empty);
                    using (var writer = new StreamWriter(Path.Combine(path, "test.log")))
                    {
                        var reporter = new ResultReporter(testResult, new ExtendedTextWrapper(writer));
                        reporter.ReportResults();
                    }
                }

                return ActionResultType.OK;
            }));
            //Terminate();
        }

        public override void Dispose()
        {
            _writer.Flush();
            _writer.Close();
            _engine = null;
        }

        public void OnTestEvent(string report)
        {
            _writer.WriteLine(report);
        }

        private void Terminate()
        {
            var processes = Process.GetProcessesByName("AIMP");

            foreach (var process in processes)
            {
                process.Kill();
                process.WaitForExit();
                process.Dispose();
            }
        }
    }
}

